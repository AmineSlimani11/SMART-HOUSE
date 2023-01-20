//--------------------------------ULTRASON_INIT-------------------------
#define trigPin 12
#define echoPin 13

//--------------------------------RFID_INIT-------------------------
#include <SPI.h>
#include <MFRC522.h>


//--------------------capteur_de_présence_INIT-----------------------

int mouvPin = 21;    // sortie du capteur 


//-----------------------
int motorPlus = 15;
int motorMinus = 16;
//---------------------------température-------------------
/*int Moteur_p1=8;
int Moteur_p2=8;*/

//-------------------------capteur_de_fumée_INIT------------------------------------
int smokeA3 = A3;

int sensorThres2 =300;


//---------------------------------RFID_INIT---------------------------------------
#define RST_PIN 49
#define SS_PIN 53
 
byte readCard[4];
String MasterTag = "8BE263B";  // REPLACE this Tag ID with your Tag ID!!!
String tagID = "";
 
// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);

//----------------------------CLAVIER_INIT-------------------------------

#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>


Servo myservo;
int pos=0; // position of servo motor
LiquidCrystal lcd(1,2,4,5,6,7);
const byte rows=4;
const byte cols=3;
 
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={31,33,35,37};
byte colPins[cols]={41,43,45};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="0000";
int currentposition=0;
 
void setup()
{
  //------CLAVIER+CODE---------
displayscreen();
//Serial.begin(9600);
//myservo.attach(9); //Servo motor connection
 

//-----------------------------------------RFID_SETUP-----------------------------

pinMode(motorPlus,OUTPUT);
pinMode(motorMinus,OUTPUT);
pinMode(9, OUTPUT); 
pinMode(10, OUTPUT); 
SPI.begin(); // SPI bus
mfrc522.PCD_Init(); // MFRC522


//-----------------------ULTRASON-----------------


pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(22, OUTPUT);


//---------------------------------------

lcd.begin(16,2);
 

 //-----------------------capteur_du_présence_SETUP------------------------------------
  pinMode(mouvPin, INPUT);
  pinMode(20, OUTPUT);         //  Entree du relais


  //-----------------------------température-----------------------------------
 /* pinMode(Moteur_p1, OUTPUT);
  pinMode(Moteur_p2, OUTPUT);*/

//--------------------------------------capteur_de_fumée_SETUP--------------------------------

  pinMode(smokeA3, INPUT);
  pinMode(19, OUTPUT); // buzzer +
  pinMode(18, OUTPUT); // buzzer -

  //----------------------------------

  pinMode(17, OUTPUT);     
}
 
void loop()
{

//----------------------------------------capteur_de_fumée_CODE---------------------------------------------

int analogSensor = analogRead(smokeA3); // lire l'entrée analog


if (analogSensor > sensorThres2)
{

  digitalWrite(18, HIGH);      // Activer l'alarme
  digitalWrite(19, LOW);
    //delay(1000);

}
else
{

  digitalWrite(19, LOW);     // Désactiver l'alarme
  digitalWrite(18, LOW);
  //delay(1000);

}

//-----------------------------------------------------ULTRASON_CODE-----------------------------------

long duration, distance;
digitalWrite(trigPin, LOW); // Added this line
delayMicroseconds(2); // Added this line
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); // Added this line
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1; // conversion in cm

//---------------------------------------

if(duration<500){
    digitalWrite(22, HIGH);   //Turn off relay
      //delay(5000);

}
else {
  
    digitalWrite(22, LOW);   //Turn off relay

    
}


 
//-------------------------------------------------------DOOR_LOCK_CODE----------------------------------
if( currentposition==0)
{
displayscreen();
 
}
int l ;
char code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("MOT DE PASSE:");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for(l=0;l<=currentposition;++l)
{
lcd.print("*");
//keypress();
}
if (code==password[currentposition])
{
++currentposition;
if(currentposition==4)
{
 digitalWrite(17, HIGH);   //Turn on relay
unlockdoor();
currentposition=0;
}
}
else
{
++currentposition;
if(currentposition==4)
{
incorrect();
currentposition=0;
}
}
}




//-----------------------------------------------------RFID_CODE-----------------------------------

 digitalWrite(9, HIGH); 
  //Wait until new tag is available
  while (getID()) 
  {
     
    if (tagID == MasterTag) 
    {
            
      digitalWrite(9, LOW); 
      digitalWrite(10, HIGH);            //  ALLUMER LA LED EN BLEU

      digitalWrite(motorPlus,HIGH);     // MONTER LA PORTE DU GARAGE
      digitalWrite(motorMinus,LOW);
      delay(3000);
      digitalWrite(motorPlus,LOW);      //  ARRETER LE MOTEUR PENDANT 3 SECONDES
      digitalWrite(motorMinus,LOW);
      delay(3000);
      digitalWrite(motorPlus,LOW);     // DESCENDRE LA PORTE
      digitalWrite(motorMinus,HIGH);
      delay(3000);
      digitalWrite(motorPlus,LOW);     // ARRETER LE MOTEUR 
      digitalWrite(motorMinus,LOW);
      digitalWrite(9, HIGH); 
      digitalWrite(10, LOW); 
    }
   
    delay(2000);
    
  }

  //----------------------------------------------Capteur_de_présence-----------------------------
  if(digitalRead(mouvPin) == HIGH)
  {
    digitalWrite(20, HIGH);      // ACTIVER LE RELAIS
  }

  else
  {
    digitalWrite(20, LOW);     //  DESACTIVER LE RELAIS
  }


 //----------------------------------------------Capteur_de_température-----------------------------------------------------
/*
int val = analogRead(A0);

float Vout = (val*5)/(1023*1000);
float temp = Vout/10;
if (temp<=15){
  digitalWrite(Moteur_p1,HIGH);
  digitalWrite(Moteur_p2,LOW);
  }
*/

}







boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}





//------------------ Function 1- OPEN THE DOOR--------------//
 
void unlockdoor()
{
delay(900);
 
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Acces AUTORISEE");
lcd.setCursor(4,1);
lcd.println("BIENVENUE!!");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(16,1);
lcd.println(" ");
lcd.setCursor(14,1);
lcd.println(" ");
lcd.setCursor(13,1);
lcd.println(" ");

for(pos = 180; pos>=0; pos-=5) // open the door
{
myservo.write(pos); 
delay(5); 
}
delay(2000);
 
 
 
delay(1000);
counterbeep();
 
delay(1000);
 
for(pos = 0; pos <= 180; pos +=5) // close the door
{ // in steps of 1 degree
myservo.write(pos); 
delay(15);
 
 
currentposition=0;
 
lcd.clear();
displayscreen();
 
}
}
 
//--------------------Function 2- Wrong code--------------//
 
void incorrect()
{
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("CODE");
lcd.setCursor(6,0);
lcd.print("INCORRECT");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(4,1);
lcd.println("ELOIGNER VOUS!!!");
 
lcd.setCursor(13,1);
lcd.println(" ");
Serial.println("CODE INCORRECT ACCES N'EST PAS AUTORISE");
delay(3000);
lcd.clear();
displayscreen();
}
//-------Function 3 - CLEAR THE SCREEN--------------------/
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}

//------------Function 4 - DISPLAY FUNCTION--------------------//
void displayscreen()
{
 
lcd.setCursor(0,0);
lcd.println("*ENTRER LE CODE*");
lcd.setCursor(1 ,1);
 
lcd.println("POUR OUVRIR LA PORTE!!");
}


 
//--------------Function 5 - Count down------------------//
void counterbeep()
{
delay(1200);
 
 
lcd.clear();
 
lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(2,0);
delay(200);
lcd.println("ENTRER DANS:::");
 
lcd.setCursor(4,1);
lcd.print("5");
delay(200);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("ENTRER DANS:");
delay(1000);
lcd.setCursor(2,0);
lcd.println("ENTRER DANS:");
lcd.setCursor(4,1); //2
lcd.print("4");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("ENTRER DANS:");
delay(1000);

lcd.setCursor(2,0);
lcd.println("ENTRER DANS:");
lcd.setCursor(4,1); 
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("ENTRER DANS:");
delay(1000);

lcd.setCursor(2,0);
lcd.println("ENTRER DANS:");
lcd.setCursor(4,1); 
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("ENTRER DANS:");
delay(1000);

lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("ENTRER DANS::");

delay(1000);
delay(40);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-FERMER");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("FERMEE!");
delay(440);
}

//----------------------------------------------------------------------------------------------------








