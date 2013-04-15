/*
  HC-SR04 test
 
 */
#include <Servo.h>

// digital pin 2 has a pushbutton attached to it. Give it a name:
int trigPin = 7;
int echoPin = 6;
int servoPin = 11;
int ledPin = 13;

Servo sonarServo;

unsigned long duration;
unsigned long distance;
unsigned long revTime=0;
char servoDir = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  sonarServo.attach(servoPin);
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
  
  if ( distance < 8 )
  {
    digitalWrite(ledPin, LOW);
  }
  else
  {
    digitalWrite(ledPin, HIGH);
  }
  
  if (millis() > revTime)
  {
    revTime = millis() + 5000;
    
    if (servoDir == 0)
    {
      servoDir = 1;
      sonarServo.write(45);
    }
    else
    {
      servoDir = 0;
      sonarServo.write(135);
    }
  }
  
  
  // print out the state of the button:
  Serial.println(distance);
  delay(50);        // delay in between reads for stability
}



