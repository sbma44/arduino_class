void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
}

void loop()
{  
  Serial.println("I have been awake for " + String(millis()) + " milliseconds.");
  
  delay(random(1000, 9000));
}

