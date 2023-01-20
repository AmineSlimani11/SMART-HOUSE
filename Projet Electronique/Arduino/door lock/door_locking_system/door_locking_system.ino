#define PIR 47
int motion = 0;

void setup()
{
	Serial.begin(9600);
	Serial.println();
	Serial.println("+----------------+");
	Serial.println("| HC-SR501 ALARM |");
	Serial.println("+----------------+");
	Serial.println();

	pinMode(PIR, INPUT);
}

void loop()
{
	//  digitalWrite(LED, digitalRead(PIR));

	int motion = digitalRead(PIR);

	if (motion == HIGH)
	{
		Serial.println("Intruder alert!");
		delay(500);
	}
	else
	{
Serial.println("nobody!");
	}
}
