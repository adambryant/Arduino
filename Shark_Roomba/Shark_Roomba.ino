/*
  Shark hand held vac using a subsumption architecture.
  
 */
#include <Servo.h>

#define LEDPIN  13
#define LEFTREAR    2
#define LEFTFRONT   3
#define RIGHTFRONT  4
#define RIGHTREAR   8
#define LEFTSERVO   9
#define RIGHTSERVO  10
#define BRUSHMOTOR  11
#define VOLTAGEPIN  A0

// Movements
#define LEFT_FWD()   leftServo.write(180);
#define RIGHT_FWD()  rightServo.write(0);
#define LEFT_BACK()  leftServo.write(0);
#define RIGHT_BACK() rightServo.write(180);
#define LEFT_STOP()  leftServo.write(90);
#define RIGHT_STOP() rightServo.write(90);

// Times
#define BACKUP_TIME  (millis() + 1000)
#define TURN_TIME    (millis() + 500 + random(750))
#define GLOBAL_TIME  (millis() + 180000);

// Behaviors
#define C_NONE      0
#define C_STOP      1
#define C_FORWARD   2
#define C_REVERSE   3
#define C_TURNLEFT  4
#define C_TURNRIGHT 5

//Servo sonarServo;
Servo leftServo;
Servo rightServo;

unsigned long duration;
unsigned long distance;
unsigned long globalExpireTime=0;
char state = 0;
char avoidDir = -1;
boolean checkVoltageFlag = false;

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  pinMode(LEDPIN, OUTPUT);
  pinMode(LEFTREAR, INPUT);
  pinMode(LEFTFRONT, INPUT);
  pinMode(RIGHTFRONT, INPUT);
  pinMode(RIGHTREAR, INPUT);
  pinMode(BRUSHMOTOR, OUTPUT);
  
  leftServo.attach(LEFTSERVO);
  rightServo.attach(RIGHTSERVO);
  
  globalExpireTime = GLOBAL_TIME;
}

// the loop routine runs over and over again forever:
void loop() 
{
  char command = C_NONE;
  
  checkAvoidDir();
  
  // Arbitrate, highest priority tasks first
  //if ( command == C_NONE ) command = rest();
//  if ( command == C_NONE ) command = detectSwitch();
  if ( command == C_NONE ) command = detectVoltage();
  if ( command == C_NONE ) command = detectIR();
  if ( command == C_NONE ) command = drive();

  motorOutput( command );   
}

void checkAvoidDir()
{
  if (millis() > globalExpireTime)
  {
    globalExpireTime = GLOBAL_TIME;
    if (avoidDir == -1)
      avoidDir = 1;
    else
      avoidDir = -1;
      
    checkVoltageFlag = true;
  }
}

void motorOutput( char command )
{
  switch ( command )
  {
    case C_NONE:                               break;
    case C_STOP:    LEFT_STOP(); RIGHT_STOP(); break;
    case C_FORWARD: LEFT_FWD(); RIGHT_FWD();   break;
    case C_REVERSE: LEFT_BACK(); RIGHT_BACK(); break;
    case C_TURNLEFT: LEFT_BACK(); RIGHT_FWD(); break;
    case C_TURNRIGHT: LEFT_FWD(); RIGHT_BACK(); break;
  }
}

void fullStop()
{
  LEFT_STOP();
  RIGHT_STOP();
  digitalWrite(BRUSHMOTOR, LOW);
  
//  sonarServo.detach();
//  leftServo.detach();
//  rightServo.detach();
}

// Rest for 1 minute out of every 3
/*
char rest()
{
  static char state = 0;
  static unsigned long expireTime = millis() + 120000;
  char retval = C_NONE;

  switch (state)
  {
    case 0:
      if (millis() > expireTime)
      {
        expireTime = millis() + 60000;
        state++;
      }
      break;
      
    case 1:
      if (millis() > expireTime)
      {
        expireTime = millis() + 120000;
        state = 0;
      }
      retval = C_STOP;
      break;
  }
  
  return retval;
}
*/

char detectVoltage()
{
  if (!checkVoltageFlag)
    return C_NONE;
  
  int volts = analogRead(VOLTAGEPIN);
 
  if ( volts > 700 )
    return C_NONE;
  else
    return C_STOP;
}

char detectIR()
{
  static char state = 0;
  char retval = C_NONE;
  static char dir = 0;
  
  switch (state)
  {
    case 0:
      if (digitalRead(LEFTREAR) == LOW)
      {
        dir = 1;
        state++;
      }
      else if (digitalRead(LEFTFRONT) == LOW)
      {
        dir = 0;
        state++;
      }
      else if (digitalRead(RIGHTFRONT) == LOW)
      {
        dir = 0;
        state++;
      }
      else if (digitalRead(RIGHTREAR) == LOW)
      {
        dir = -1;
        state++;
      }
      break;
      
    case 1:
      retval = avoid(dir);
        
      if ( retval == C_NONE )
      {
        state = 0;
      }
      break;
  }

  return retval;
}

/*
  Implements a standard avoidance routine of:
    1. Back up for x seconds
    2. Turn for x seconds
  
  Direction of turn is:
    -1  - turn left
    0   - random direction
    1   - turn right  
    
  This routine counts on retval retaining its value from one call to the next
*/    
char avoid( char dir )
{
  static char state = 0;
  static unsigned long expireTime;
  static char retval = C_NONE;
  
  switch (state)
  {
    case 0:
      expireTime = BACKUP_TIME; //millis() + 1000; //+ 500 + random(1,1500);
      state++;
      retval = C_REVERSE;
      break;
      
    case 1:
      if (millis() > expireTime)
      {
        expireTime = TURN_TIME;  //millis() + 1000; //500 + random(1,1500);
        state++;
        switch (dir)
        {
          case -1: retval = C_TURNLEFT; break;
          case  0: retval = random(C_TURNLEFT, C_TURNRIGHT + 1); break;
          case  1: retval = C_TURNRIGHT; break;
        }
      }
      break;
      
    case 2:
      if (millis() > expireTime)
      {
        state = 0;
        retval = C_NONE;
      }
      break;  
   }
  
  return retval;
}

char drive()
{
  digitalWrite( BRUSHMOTOR, HIGH );
  return C_FORWARD;
}

