// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
#include <Wire.h>

#define SLAVE 0x26

void setup()
{
  pinMode(11,OUTPUT);
  Serial.begin(9600);	// Debugging only
  Serial.println("setup");

  Wire.begin(); // join i2c bus (address optional for master)

    // Initialise the IO and ISR
//    vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(4);
  vw_setup(2000);	 // Bits per sec

  vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (Serial.available() > 0)
    {
      uint8_t incoming = Serial.read();
      Wire.beginTransmission(SLAVE); // transmit to device #4
      Wire.write(incoming);              // sends one byte  
      Wire.endTransmission();    // stop transmitting
    }

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;

        digitalWrite(11, false); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
	Serial.print("Got: ");
	
	for (i = 0; i < buflen; i++)
	{
            char c = buf[i];
	    Serial.print(c);
	    Serial.print(" ");
	}
	Serial.println("");
        digitalWrite(11, true);
    }
}
