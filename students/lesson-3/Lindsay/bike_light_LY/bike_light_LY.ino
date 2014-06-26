byte incomingByte = 0; // incoming serial byte

int buttonPin = 4;

int ledPin_R = 13;
int ledPin_G = 12;
int ledPin_B = 11;

int currentPinMode = 0;

station = 0

/* debounce variables */
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;

void setup(){
  // start serial port at 9600 bps:
  Serial.begin(9600);
   
  randomSeed(analogRead(0));
  
  pinMode(buttonPin, INPUT);
    // set pin 4 for input, pin 11-13 for output
  pinMode(ledPin_R, OUTPUT);
  pinMode(ledPin_G, OUTPUT);
  pinMode(ledPin_B, OUTPUT);

  // turn off all those LEDs by setting them HIGH  
  digitalWrite(ledPin_R, HIGH);
  digitalWrite(ledPin_G, HIGH);
  digitalWrite(ledPin_B, HIGH);
  
}


void loop(){
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only change the LED mode if the new button state is LOW
      if (buttonState == LOW) {
        currentPinMode = currentPinMode + 1;
        
        if (currentPinMode == 2) {
          Serial.println("even");
        }
        else{
           Serial.println("odd");
        } 
        if (currentPinMode = 2) {
          currentPinMode = 0;
        } 
      } 
    }
  }


  // is there a byte waiting for us on the serial port?
  if (Serial.available() > 0) {

    // get incoming byte
    incomingByte = Serial.read();
    
    // ensure that incoming byte is a capital letter
    if ((incomingByte >= 'A') && (incomingByte <= 'Z')) {
      if (incomingByte == 'R'){
        digitalWrite(ledPin_R, LOW);
        digitalWrite(ledPin_G, HIGH);
        digitalWrite(ledPin_B, HIGH);
      }  
      if (incomingByte == 'G'){
        digitalWrite(ledPin_R, HIGH);
        digitalWrite(ledPin_G, LOW);
        digitalWrite(ledPin_B, HIGH);
      }
      if (incomingByte == 'Y'){
        digitalWrite(ledPin_R, LOW);
        digitalWrite(ledPin_G, LOW);
        digitalWrite(ledPin_B, HIGH);

      }
    }
  } 
 lastButtonState = reading;  
}

