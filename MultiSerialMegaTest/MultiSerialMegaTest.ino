/*
  This program is meant to help test the MercuryBoard's RS232 ports when using an Arduino Mega 2560.
  Make sure to all jumpers are in place for testing! 
  If you are using USB, don't put jumpers on RX/TX 0, and jumper RX/TX 1 to RS232. 
  The built in LED on Pin 13 will blink briefly when a message is received. 
  
  Send a message to any port, prepended with a number between 0 and 3. 
  After a confirmation, The message will be sent out the corresponding port number.

  For example, sending "1 Hello Port One" will result in Port 1 sending "Hello Port One".

  ChangeLog:
  Version 1.0 - Initial Release

*/
const byte LED = 13; //an LED to blink so we know the sketch is running
const byte buffersize = 64;

char theMessage[buffersize];
boolean LEDstatus = false;
uint8_t ReadPort = 0;
uint8_t i = 0;
//create a pointer for making it simpler to check each serial port...
HardwareSerial *InputPort;

void setup() {
  //All Serial Ports are 9600 baud...
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  Serial.println("Beginning Multiple Serial Port Test");
  Serial.println("Prepend your Message with a number and space");
  Serial.println("To send the message out that port");
  Serial.println("Messages are terminataed with carriage return only");

  Serial.println();
}

void loop() {

  if (i > 3) 
  {
    i = 0;
  }
  switch (i) 
  {
    case 0:
      InputPort = &Serial;
      break;
    case 1:
      InputPort = &Serial1;
      break;
    case 2:
      InputPort = &Serial2;
      break;
    case 3:
      InputPort = &Serial3;
      break;
    default:
      InputPort = &Serial;
      break;
  }
  if (InputPort->available()) 
  {
    digitalWrite(LED, HIGH);
    uint8_t OutputPortNumber = InputPort->parseInt(); // get that port number
    InputPort->read();//Read one byte and throw it away - get rid of the space after the port number
    InputPort->readBytesUntil('\r', theMessage, buffersize);
    InputPort->print("Sending a message to Port ");
    InputPort->println(OutputPortNumber);
    switch (OutputPortNumber)
    {
      case 0:
        Serial.println(theMessage);
        break;
      case 1:
        Serial1.println(theMessage);
        break;
      case 2:
        Serial2.println(theMessage);
        break;
      case 3:
        Serial3.println(theMessage);
        break;
      default:
        Serial.println(theMessage);
        break;
    }
    memset(theMessage, 0, sizeof(theMessage));
    digitalWrite(LED, LOW);
  }
   i++;
}

