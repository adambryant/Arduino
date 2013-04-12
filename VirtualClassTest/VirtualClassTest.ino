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
#define LEFT_FWD()   leftServo.write(180)
#define RIGHT_FWD()  rightServo.write(0)
#define LEFT_BACK()  leftServo.write(0)
#define RIGHT_BACK() rightServo.write(180)
#define LEFT_STOP()  leftServo.write(90)
#define RIGHT_STOP() rightServo.write(90)

Servo leftServo;
Servo rightServo;

class Behavior
{
  public: 
    virtual boolean takeControl() { return false; }
    virtual void action() {}
    virtual void suppress() {}
};

class Drive : public Behavior
{
  public:
    boolean takeControl()
    {
      Serial.println("In takeControl");
      return true;
    }
    void action()
    {
      Serial.println("In action");
//      LEFT_FWD();
//      RIGHT_FWD();
      leftServo.write(180);
      rightServo.write(0);
    }
    void suppress()
    {
      LEFT_STOP();
      RIGHT_STOP();
    }
};

class CheckIR : public Behavior
{
  public:
    boolean takeControl()
    {
      return false;
    }
    void action()
    {
    }
};

#define NUM_BEHAVIORS  2
Behavior behaviors[NUM_BEHAVIORS];

Drive bDrive;
CheckIR bCheckIR;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  behaviors[0] = bDrive;
  behaviors[1] = bCheckIR;

  leftServo.attach(LEFTSERVO);
  rightServo.attach(RIGHTSERVO);
}

void loop() 
{
  // put your main code here, to run repeatedly: 
  for (int i=0; i<NUM_BEHAVIORS; i++)
  {
    Serial.println(i);
    
    if ( behaviors[i].takeControl() == true )
    {
      Serial.println("y");
      behaviors[i].action();
    }
//    bDrive.takeControl();
//    bDrive.action();
  }
  delay(500);
}
