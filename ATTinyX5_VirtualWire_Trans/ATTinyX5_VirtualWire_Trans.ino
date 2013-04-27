// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
#include <TinyWireS.h>

#define LEDPIN  1

#define I2C_SLAVE_ADDR  0x26            // i2c slave address (38)

char byteRcvd[1];

void setup()
{
  pinMode(LEDPIN, OUTPUT);
//    Serial.begin(9600);	  // Debugging only
//    Serial.println("setup");

    // Initialise the IO and ISR
//    vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_tx_pin(4);
  vw_setup(2000);	 // Bits per sec

  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
}

void loop()
{
    char *msg = "hello";

  if (TinyWireS.available())
  {
    digitalWrite(LEDPIN, true); // Flash a light to show transmitting
    byteRcvd[0] = TinyWireS.receive();     // get the byte from master
//    Blink(LEDPIN, byteRcvd - '1');
//    msg[0] = byteRcvd;
//    vw_send((uint8_t *)msg, 5);
    vw_send((uint8_t *)byteRcvd,1);
    vw_wait_tx(); // Wait until the whole message is gone
//    delay(200);
    digitalWrite(LEDPIN, false);
//    delay(200);
  }
}

void Blink(byte led, byte times)
{ // poor man's display
  for (byte i=0; i< times; i++)
  {
    digitalWrite(led,HIGH);
    delay (50);
    digitalWrite(led,LOW);
    delay (50);
  }
}


