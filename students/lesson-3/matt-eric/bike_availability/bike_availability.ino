byte incomingByte = 0; // incoming serial byte

int g = 13;
int b = 12;
int r = 11;

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  
  // set pin 13 to OUTPUT
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  
  digitalWrite(r, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  
  Serial.println("I'M BEGINNING TO LIVE");
}

void loop()
{
  
  // is there a byte waiting for us on the serial port?
  if (Serial.available() > 0) {
    
    // get incoming byte
    incomingByte = Serial.read();
    
    if (incomingByte == 'Y') {
      Serial.println("I JUST GOT A Y");
      digitalWrite(g, LOW);
      digitalWrite(r, HIGH);
    }
    else if (incomingByte == 'M') {
     Serial.println("I JUST GOT AN M");
      digitalWrite(g, LOW);
      digitalWrite(r, LOW);      
    }
    else if (incomingByte == 'N') {
     Serial.println("I JUST GOT AN N");
      digitalWrite(g, HIGH);
      digitalWrite(r, LOW);
    }

    
    //Serial.println("I'M BLINKING " + String(numberOfTimesToBlink) + " TIMES AND I'M SO HAPPY");   
  }
}
