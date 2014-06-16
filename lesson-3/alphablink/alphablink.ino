byte incomingByte = 0; // incoming serial byte
int ledPin = 13; // LED output pin

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  
  // set pin 13 to OUTPUT
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // is there a byte waiting for us on the serial port?
  if (Serial.available() > 0) {

    // get incoming byte
    incomingByte = Serial.read();
    
    // ensure that incoming byte is a capital letter
    if ((incomingByte >= 'A') && (incomingByte <= 'Z')) {

      // how many times should we blink?
      int numberOfTimesToBlink = (incomingByte - 'A') + 1;

      // okay, blink that many times
      for(int i=0; i < numberOfTimesToBlink; i++) {
        digitalWrite(ledPin, HIGH);
        delay(200);
        digitalWrite(ledPin, LOW);
        delay(200);
      }
    }           
  }
}
