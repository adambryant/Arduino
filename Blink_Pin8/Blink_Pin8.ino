/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
 #define PIN 8

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(PIN, OUTPUT);     
}

void loop() {
  digitalWrite(8, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(8, LOW);    // set the LED off
  delay(1000);              // wait for a second
}
