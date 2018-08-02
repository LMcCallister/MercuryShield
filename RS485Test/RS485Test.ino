
/*
  This program is meant to help test the MercuryBoard's RS485 functions.

  This program is made to work with an Arduino Mega, since you can use USB on Port 0 and
  RS485 on Port 1. For setup, Leave jumpers off of RX/TX 0, and connect RX/TX 1 to RS485, with 485Mode
  jumpered to P2.

  By default, the RS485 serial channel is in "listen" mode. When a message is sent over USB, it is repeated
  over RS485. Similarly, when a message is received over RS485, it is repeated over the USB comm port.

  For visual feedback, the built in LED pin 13 mirrors the state of Pin 2 which controls the direction of
  data on the RS485 chip. When the LED is off, pin 2 is Low, and the RS485 channel is set to recieve data.

  Both ports are set to 9600 baud, 8 bits, No Parity 1 stop bit.


  ChangeLog:
  Version 1.0 - Initial Release

*/

const uint8_t LED = 13;
const uint8_t Control = 2;
const byte buffersize = 64;

char theMessage[buffersize];


void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(Control, OUTPUT);
  
  Serial.begin(9600);
  Serial1.begin(9600);

  digitalWrite(LED, LOW);
  digitalWrite(Control, LOW);
  Serial.println("RS485 Test Ready. Send a message over USB (Port 0) or RS485 (Port 1) to see it echoed on the other port");


}

void loop()
{
  if (Serial.available()) {
    Serial.readBytesUntil('\r', theMessage, buffersize);
    Serial.println("Sending Message...");
    digitalWrite(LED, HIGH);
    digitalWrite(Control, HIGH);
    Serial1.println(theMessage);
    Serial1.flush();//wait for the message to finish transmitting
    delayMicroseconds(10);
    digitalWrite(LED, LOW);
    digitalWrite(Control, LOW);
    memset(theMessage, 0, sizeof(theMessage));
  }

  if (Serial1.available()) {
    Serial1.readBytesUntil('\r', theMessage, buffersize);
    Serial1.flush();//wait for the message to finish transmitting
    delayMicroseconds(10);
    digitalWrite(LED, LOW);
    digitalWrite(Control, LOW);
    Serial.println(theMessage);
    Serial.flush();//wait for the message to finish transmitting
    memset(theMessage, 0, sizeof(theMessage));
  }

  
}
