#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(1,2,4,5,6,7);

int motorPlus = 15;
int motorMinus = 16;

#define RST_PIN 49
#define SS_PIN 53
 
byte readCard[4];
String MasterTag = "8BE263B";  // REPLACE this Tag ID with your Tag ID!!!
String tagID = "";
 
// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() 
{
  pinMode(motorPlus,OUTPUT);
  pinMode(motorMinus,OUTPUT);
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  lcd.begin(16,2);
  SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // MFRC522
  lcd.clear();
  lcd.print(" Access Control ");
  lcd.setCursor(0, 1);
  lcd.print("Scan Your Card>>");
}
 
void loop() 
{
  digitalWrite(9, HIGH); 
  //Wait until new tag is available
  while (getID()) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
     
    if (tagID == MasterTag) 
    {
            
      digitalWrite(9, LOW); 
      digitalWrite(10, HIGH); 
      lcd.print(" Access Granted!");
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
    else
    { 
      lcd.print(" Access Denied!");
       
    }
    
       
    delay(2000);
    lcd.clear();
    lcd.print(" Access Control ");
    lcd.setCursor(0, 1);
    lcd.print("Scan Your Card>>");
  }
}
 
//Read new tag if available
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
