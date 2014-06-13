int buttonPin = 4;

int ledPin_R = 13;
int ledPin_G = 12;
int ledPin_B = 11;
int t1 = 0;
int t2 = 0;
String message = "";

int currentPinMode = 2;
int pressLag = 0;

/* debounce variables */
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  // set pin 4 for input, pin 11-13 for output
  Serial.begin(9600);
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
      if (buttonState == LOW) {
        //OK, now that everything is debounced, we know that the button has really been pressed
        //when button is pressed, record current time in t1
        t1 = millis();
      }
      
      if (buttonState == HIGH){
        //when button is released, record current time in t2. t2-t1 = the time the button was depressed for
        t2 = millis();
        if( (t2 - t1) <= 300 ){
          //this is the morse code part, define a press under 300 ms as "short" (could fiddle w/ this, or find actual
          //military best practices, this decision was pretty arbitrary, based on trial and error)
          message += '.';
        }
        
        else if( (t2 - t1) > 300){
          //otherwise, if button is depressed more than 300 ms, record it as "long"
          message += '-';
        }
        //print the current morse code message to Serial (Tools > Serial Monitor to view this output)
        Serial.println(message)
        
          if( (contains(message,"...---...")) == 1){
            //every loop, check the message to see if it contains 'SOS' in morse code, any
            //where within the message (see below for the contains() method
            //If it does, turn the led to red
            currentPinMode = 0;
            Serial.println(currentPinMode);
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



bool contains(String s, String search) {
  //a bit of a wonky method, the `substring()` method needs to know exactly where to look for
  //the substring. So, this loop iterates through the whole message, looking at chunks of characters as long as
  //the substring (in this case, "...---..."), and seeing if there's a match
    int max = s.length() - search.length();

    for (int i = 0; i <= max; i++) {
        if (s.substring(i) == search) return true; // or i
    }

    return false; //or -1
} 