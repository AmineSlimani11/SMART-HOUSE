char Incoming_value = 0;

#include <LiquidCrystal.h>
// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(1,2,4,5,6,7);

void setup() {
lcd.begin(16,2);
pinMode(13,OUTPUT);
// set cursor position to start of first line on the LCD
lcd.setCursor(0,0);
lcd.print("JE M'appelle OSWA !");
Serial.begin(9600);
}
void loop()
{
  if(Serial.available() > 0)  
  { 
    lcd.clear(); 
    lcd.print(Serial.read()); 
              

  }

}