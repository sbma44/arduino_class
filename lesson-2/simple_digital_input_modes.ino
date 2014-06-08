int buttonPin = 4;

int ledPin_R = 13;
int ledPin_G = 12;
int ledPin_B = 11;

int currentPinMode = 0;

void setup() {
  // set pin 4 for input, pin 11-13 for output
  pinMode(buttonPin, INPUT);
  pinMode(ledPin_R, OUTPUT);
  pinMode(ledPin_G, OUTPUT);
  pinMode(ledPin_B, OUTPUT);

  // turn off all those LEDs by setting them HIGH  
  digitalWrite(ledPin_R, HIGH);
  digitalWrite(ledPin_G, HIGH);
  digitalWrite(ledPin_B, HIGH);
}

void loop() {
  // read input
  int reading = digitalRead(buttonPin);

  // advance our mode by 1 if the pin is low
  if (reading==LOW){
    currentPinMode = currentPinMode + 1;
    if (currentPinMode>3) {
      currentPinMode = 0;
    }
  }
  
  switch (currentPinMode) {
    case 0: // red
      digitalWrite(ledPin_R, LOW);
      digitalWrite(ledPin_G, HIGH);
      digitalWrite(ledPin_B, HIGH);
      break;
      
    case 1: // green  
      digitalWrite(ledPin_R, HIGH);
      digitalWrite(ledPin_G, LOW);
      digitalWrite(ledPin_B, HIGH);
      break;
      
    case 2: // blue
      digitalWrite(ledPin_R, HIGH);
      digitalWrite(ledPin_G, HIGH);
      digitalWrite(ledPin_B, LOW);
      break;        
  }
}
