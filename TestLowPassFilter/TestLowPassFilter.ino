/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
int outValue = 0;
long sum;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int count = 0;
  analogWrite(3, outValue);
  while (count++ < 20)
  {
    // read the input on analog pin 0:
    sum = 0;
    for (int i=0; i< 20; i++)
    {
      int sensorValue = analogRead(A0);
      sum += sensorValue;
      delay(10);
    }
    // print out the value you read:
    Serial.print("out: ");
    Serial.print(outValue);
    Serial.print("  in: ");
    Serial.println(sum / 20);    //sensorValue);
    delay(250);        // delay in between reads for stability
  }
  outValue += 10;
  if (outValue > 255)
    outValue = 0;
}
