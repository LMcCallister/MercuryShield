
uint8_t Relay[16] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 59, 58, 57, 56, 55, 54 };

void setup()
{
	for (uint8_t i = 0; i < 16; i++) {
		pinMode(i, OUTPUT);
	}

 //The arduino pin #s for analog pins don't unroll in the for loop correctly, so we have to do those manually...
	pinMode(A5, OUTPUT);
	pinMode(A4, OUTPUT);
	pinMode(A3, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A0, OUTPUT);

}

void loop()
{
	for (int8_t i = 0; i < 16; i++) {
		digitalWrite(Relay[i], HIGH);
		Serial.println(Relay[i]);
		delay(100);
	}

	delay(1000);


	for (int8_t i = 16; i > -1; i--) {
		digitalWrite(Relay[i], LOW);
		Serial.println(Relay[i]);
		delay(100);
	}

	delay(1000);

}
