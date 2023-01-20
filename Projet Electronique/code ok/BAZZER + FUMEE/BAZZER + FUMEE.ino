#include <LiquidCrystal.h>

LiquidCrystal lcd(1,2,4,5,6,7);


int smokeA0 = A3;
// Your threshold value
int sensorThres =450;

void setup() {
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  pinMode(smokeA0, INPUT);
  pinMode(9, OUTPUT);
  pinMode(30, OUTPUT);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    lcd.print("Gaz detected !!");
    lcd.print( analogSensor);
    digitalWrite(9, HIGH);
    digitalWrite(30, LOW);
     delay(1000);
    lcd.clear();
  }
  else
  {
    lcd.print("NOT detected !!");
    lcd.print( analogSensor);
    digitalWrite(9, LOW);
    digitalWrite(30, LOW);
    delay(1000);
    lcd.clear();
  }
}
