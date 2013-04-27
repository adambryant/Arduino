// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

#define SLAVE 0x26
#define LED  13

boolean ledOn = false;

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  // while the serial stream is not open, do nothing:
//   while (!Serial) ;
  pinMode(LED, OUTPUT);     
}

//byte x = B01010101;
byte x = 0;

void loop()
{
  ledOn = !ledOn;
  digitalWrite(LED, ledOn);
  
  Serial.print("Transmitting: ");
  Serial.println(x, DEC);
  
  Wire.beginTransmission(SLAVE); // transmit to device #4
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

//  Serial.print("Receiving: ");
//  Wire.requestFrom(SLAVE, 1);    // request 6 bytes from slave device #2
//
//  while(Wire.available())    // slave may send less than requested
//  { 
//    char c = Wire.read(); // receive a byte as character
//    Serial.println(c,DEC);         // print the character
//  }

  x++;
  if (x > 20)
    x = 0;
  delay(500);
}
