int sensorPin = A0;

int sensorValue = 0;

void setup()
{
  Serial.begin(9600);
}


void loop()
{
  int mV = 0;
  int inches = 0;
  sensorValue = analogRead(sensorPin);
  
  Serial.print("Reading: ");
  Serial.print(sensorValue);
  
  Serial.print("  mV: ");
  mV = sensorValue * 4.9;
  Serial.print(mV);

  inches = int(mV / 9.8);
  
  Serial.print("  ft: ");
  Serial.print(inches / 12);
  
  Serial.print("  in: ");  
  Serial.println(inches % 12);
  
  
  delay(50);
}



