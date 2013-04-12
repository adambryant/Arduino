/*
  Shark hand held vac using a subsumption architecture.
 
 */
#include <Servo.h>

#define LEDPIN  13
#define LEFTSW  10
#define RIGHTSW  9
#define TRIGPIN  7
#define ECHOPIN  8
#define SONARSERVO  4
#define LEFTSERVO   2
#define RIGHTSERVO  3

#define LEFT_FWD   leftServo.write(180);
#define RIGHT_FWD  rightServo.write(0);
#define LEFT_BACK  leftServo.write(0);
#define RIGHT_BACK rightServo.write(180);
#define LEFT_STOP  leftServo.write(90);
#define RIGHT_STOP rightServo.write(90);

#define STOP     0
#define FORWARD  1
#define REVERSE  2
#define TURNLEFT  3
#define TURNRIGHT 4

Servo sonarServo;
Servo leftServo;
Servo rightServo;

unsigned long duration;
unsigned long distance;
unsigned long revTime=0;
char servoDir = 0;
char state = 0;

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // make the pushbutton's pin an input:
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(LEFTSW, INPUT);
  pinMode(RIGHTSW, INPUT);
  
  sonarServo.attach(SONARSERVO);
  leftServo.attach(LEFTSERVO);
  rightServo.attach(RIGHTSERVO);
}

// the loop routine runs over and over again forever:
void loop() 
{
  switch( state )
  {
    case 0:    // drive
      state = drive();
      break;
      
    case 1:    // detect
      state = detect();
      break;
      
    case 2:    // avoid
      state = avoidLeft();
      break;
      
    case 3:    // avoid
      state = avoidRight();
      break;
      
    case 4:    // rest
      state = rest();
      break;
  }
}

char drive()
{
  LEFT_FWD;
  RIGHT_FWD;
  return 1;
}

char detect()
{
  static char state = 0;
  static unsigned long expireTime = millis();
  static char dir = -1;  // values are -1, 0, 1
  
  switch( state )
  {
    case 0:  // point to next position
      digitalWrite(LEDPIN, HIGH);
      dir++;
      if ( dir > 1 )
      {
        dir = -1;
      }
        
      switch ( dir )
      {
        case -1: sonarServo.write(40); break;
        case  0: sonarServo.write(90); break;
        case  1: sonarServo.write(140); break;
      }
      expireTime = millis() + 1500;
      state++;
      break;
      
    case 1:  // wait for it to get there
      if ( millis() > expireTime )
        state++;
      break;
      
    case 2:  // Take a reading
      // pulse the trigger line
      digitalWrite(TRIGPIN, HIGH);
      delayMicroseconds(100);
      digitalWrite(TRIGPIN, LOW);
      
      // wait for the echo
      duration = pulseIn(ECHOPIN, HIGH);
      
      distance = duration / 116;
      
      Serial.println( distance );
      
      if ( distance < 10 )
      {
        digitalWrite(LEDPIN, LOW);
        state = 0;
        if (dir == -1)
          return 2;
        else
          return 3;
      }
      else
      {
        digitalWrite(LEDPIN, HIGH);
      }
        
      state = 0;
      break;
  }
  
  /*
  Serial.print("left: ");
  Serial.print(digitalRead(LEFTSW));
  Serial.print("   right: ");
  Serial.println(digitalRead(RIGHTSW));
  delay(500);
  */
  return 1;
}

char avoidLeft()
{
  static char state = 0;
  static unsigned long expireTime;
  
  switch ( state )
  {
    case 0:
      LEFT_BACK;
      RIGHT_BACK;
      expireTime = millis() + 3000;
      state++;
      break;
    
    case 1:
      if (millis() > expireTime)
      {
        state = 0;
        return 0;
      }
      break;

    case 2:
      LEFT_FWD;
      RIGHT_BACK;
      expireTime = millis() + 3000;
      state++;
      break;
      
    case 3:
      if (millis() > expireTime)
      {
        state = 0;
        return 0;
      }
      break;
  }
  
  return 2;
}

char avoidRight()
{
  static char state = 0;
  static unsigned long expireTime;
  
  switch ( state )
  {
    case 0:
      LEFT_BACK;
      RIGHT_BACK;
      expireTime = millis() + 3000;
      state++;
      break;
    
    case 1:
      if (millis() > expireTime)
      {
        state = 0;
        return 0;
      }
      break;

    case 2:
      LEFT_BACK;
      RIGHT_FWD;
      expireTime = millis() + 3000;
      state++;
      break;
      
    case 3:
      if (millis() > expireTime)
      {
        state = 0;
        return 0;
      }
      break;
  }
  
  return 3;
}

char rest()
{
  LEFT_STOP;
  RIGHT_STOP;
  return 3;
}

