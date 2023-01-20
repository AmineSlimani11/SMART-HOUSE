//* Code by satyam singh. ******
//* subscribe my youtube channel from below link
//* https://www.youtube.com/channel/UCOrVJ1fDDCKDYMAYQmn6zWw
//*
//*************************************"**********************//


#define trigPin 12
#define echoPin 13

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(1,2,4,5,6,7);

void setup()
{
lcd.begin(16, 2);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
lcd.setCursor(1,0);
lcd.print("Distance=");
}

void loop()
{
long duration, distance;
digitalWrite(trigPin, LOW); // Added this line
delayMicroseconds(2); // Added this line
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); // Added this line
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1; // conversion in cm
lcd.setCursor(11,0);
lcd.print(distance/10); //output on lcd in centimeter
lcd.setCursor(14,0);
lcd.print("mm");
}