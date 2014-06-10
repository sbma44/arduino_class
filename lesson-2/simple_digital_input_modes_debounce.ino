int buttonPin = 4;

int ledPin_R = 13;
int ledPin_G = 12;
int ledPin_B = 11;

int currentPinMode = 0;

/* debounce variables */
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


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

// If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  // only execute this code if the button has held steady for `debounceDelay` milliseconds
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only change the LED mode if the new button state is LOW
      if (buttonState == LOW) {
        currentPinMode = currentPinMode + 1;
        if (currentPinMode >= 3) {
          currentPinMode = 0;
        }
      }
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
  
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}