void setup() 
{
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  
  digitalWrite(11, LOW);
}

void loop() 
{
  // put your main code here, to run repeatedly: 
  digitalWrite(11, HIGH);
  delay(10000);
  digitalWrite(11, LOW);
  delay(5000);
}
