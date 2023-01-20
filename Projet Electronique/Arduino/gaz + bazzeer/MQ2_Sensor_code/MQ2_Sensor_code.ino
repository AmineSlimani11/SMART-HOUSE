#include <LiquidCrystal.h>

LiquidCrystal lcd(1,2,4,5,6,7);


int smokeA0 = A3;
// Your threshold value
int sensorThres =300;

void setup() {
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  pinMode(smokeA0, INPUT);
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
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
    digitalWrite(18, HIGH);
    digitalWrite(19, LOW);
     delay(1000);
    lcd.clear();
  }
  else
  {
    lcd.print("NOT detected !!");
    lcd.print( analogSensor);
    digitalWrite(19, LOW);
    digitalWrite(18, LOW);
    delay(1000);
    lcd.clear();
  }
}
