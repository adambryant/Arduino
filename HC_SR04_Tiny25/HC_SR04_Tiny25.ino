/*
  HC-SR04 test
 
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int trigPin = 1;
int echoPin = 2;
int pwmPin = 0;

unsigned long duration;
unsigned long distance;
unsigned long array[16];
char idx = 0;
unsigned long total;
//double percent;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  // make the pushbutton's pin an input:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i < 16; i++)
  {
    array[i] = 60;
  }
}

// the loop routine runs over and over again forever:
void loop() 
{
  // read the input pin:
  //int buttonState = digitalRead(pushButton);
  
  // pulse the trigger line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  
  // wait for the echo
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration / 116;
  
  if ( distance > 60 )
    distance = 60;
    
  distance *= 3;
  
  array[idx++] = distance;
  if (idx == 16)
    idx = 0;
    
  total = 0;
  for (int i = 0; i < 16; i++)
  {
    total += array[i];
  }
    
//  distance = 255 - distance;
  
  analogWrite( pwmPin, total / 16 );
  
  delay(25);
}



