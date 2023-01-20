int smokeA0 = A5;
// Your threshold value
int sensorThres =1000;

void setup() {
  pinMode(smokeA0, INPUT);
  pinMode(8, OUTPUT);
  pinMode(30, OUTPUT);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
   
    digitalWrite(8, HIGH);
    digitalWrite(30, LOW);
     delay(1000);
  }
  else
  {
    digitalWrite(8, LOW);
    digitalWrite(30, LOW);
    delay(1000);

  }
}
//----------------------------------------------------------------------------------------
int Relay = 8;
void setup()
{
  pinMode(17, OUTPUT);     //Set Pin3 as output
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
   pinMode(22, OUTPUT);
}
void loop()
{
  digitalWrite(17, HIGH);   //Turn off relay
  delay(2000);
  digitalWrite(18, HIGH);   //Turn off relay
  delay(2000);
  digitalWrite(19, HIGH);   //Turn off relay
  delay(2000);
  digitalWrite(20, HIGH);   //Turn off relay
  delay(2000);
  digitalWrite(22, HIGH);   //Turn off relay
  delay(2000);
  digitalWrite(17, LOW);    //Turn on relay
  delay(2000);
  digitalWrite(18, LOW);    //Turn on relay
  delay(2000);
  digitalWrite(19, LOW);    //Turn on relay
  delay(2000);
  digitalWrite(20, LOW);   //Turn off relay
  delay(2000);
  digitalWrite(22, LOW);   //Turn off relay
  delay(2000);
}
//---------------------------------------------------------------------------------------
