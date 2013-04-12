#include <FlexiTimer2.h>
/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
 volatile int array[5] = {512,512,512,512,512};
 volatile int idx = 0;
 volatile int last = 0;
 volatile int avg = 0;
 
void tmr2Int()
{
  int acc = analogRead(A1);
  int sum = 0;
  idx++;
  if (idx > 4)
    idx = 0;
  array[idx] = acc;
  for (int i=0; i<5; i++)
    sum += array[i];
  avg = sum / 5;
}


// the setup routine runs once when you press reset:
void setup() {
  FlexiTimer2::set(50,tmr2Int);
  FlexiTimer2::start();
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
//  int sensorValue = analogRead(A1);
  // print out the value you read:
  Serial.println(avg);
  delay(100);        // delay in between reads for stability
}
