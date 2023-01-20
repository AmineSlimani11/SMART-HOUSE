//--------------------------------ULTRASON_INIT-------------------------
#define trigPin 12
#define echoPin 13

//--------------------------------RFID_INIT-------------------------
#include <SPI.h>
#include <MFRC522.h>


int motorPlus = 15;
int motorMinus = 16;

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
  //ultrason---------------

//----------------------
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
 
}
 
void loop()
{

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

 
//-------------------------------------------------------DOOR_LOCK_CODE----------------------------------


if(duration<300){

digitalWrite(22, HIGH);   //Turn on light
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
lcd.print("PASSWORD:");
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

}

else {
digitalWrite(22, LOW);   //Turn off relay
    
}



//-----------------------------------------------------RFID_CODE-----------------------------------



 digitalWrite(9, HIGH); 
  //Wait until new tag is available
  while (getID()) 
  {
     
    if (tagID == MasterTag) 
    {
            
      digitalWrite(9, LOW); 
      digitalWrite(10, HIGH); 

      digitalWrite(motorPlus,HIGH);
      digitalWrite(motorMinus,LOW);
      delay(3000);
      digitalWrite(motorPlus,LOW);
      digitalWrite(motorMinus,LOW);
      delay(3000);
      digitalWrite(motorPlus,LOW);
      digitalWrite(motorMinus,HIGH);
      delay(3000);
      digitalWrite(motorPlus,LOW);
      digitalWrite(motorMinus,LOW);
      digitalWrite(9, HIGH); 
      digitalWrite(10, LOW); 
      // You can write any code here like opening doors, switching on a relay, lighting up an LED, or anything else you can think of.
    }
   
    delay(2000);
    
  }
 
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
lcd.print("Access Granted");
lcd.setCursor(4,1);
lcd.println("WELCOME!!");
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
lcd.println("GET AWAY!!!");
 
lcd.setCursor(13,1);
lcd.println(" ");
Serial.println("CODE INCORRECT YOU ARE UNAUTHORIZED");
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
lcd.println("*ENTER THE CODE*");
lcd.setCursor(1 ,1);
 
lcd.println("TO OPEN DOOR!!");
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
lcd.println("GET IN WITHIN:::");
 
lcd.setCursor(4,1);
lcd.print("5");
delay(200);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //2
lcd.print("4");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);

lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);

lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);

lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN::");

delay(1000);
delay(40);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
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
lcd.print("LOCKED!");
delay(440);
}

//----------------------------------------------------------------------------------------------------

