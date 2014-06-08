int buttonPin = 4;
int ledPin = 13;

void setup() {
  // set pin 4 for input, pin 13 for output
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read input
  int reading = digitalRead(buttonPin);

  // turn LED on or off, depending
  if (reading==HIGH){
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}
