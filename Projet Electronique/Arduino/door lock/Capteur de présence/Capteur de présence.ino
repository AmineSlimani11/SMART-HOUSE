int ledPin = 8;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(mouvPin, INPUT);
  pinMode(51, OUTPUT);
 
  digitalWrite(ledPin, LOW);  
}

void loop() {
  if(digitalRead(mouvPin) == HIGH)
  {
    digitalWrite(51, HIGH);
  }

  else
  {
    digitalWrite(51, LOW);
  }
}