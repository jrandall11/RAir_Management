/*
  RAir Management

  A air management system for vehicle-equipped air-ride. This system aids in airing and maintaining air pressure
  in the air system. It also provides a way to air-up or down quickly depending on user input.

  The circuit:
  * A0 - Left front airbag pressure sensor.
  * A1 - Right front airbag pressure sensor.
  * A2 - Left rear airbag pressure sensor.
  * A3 - Right rear airbag pressure sensor.

  Created 27 July 2019
  By Joshua Randall
  Modified 27 July 2019
  By Joshua Randall

*/

#include <SPI.h>
#include <Wire.h>
#include <RAirGlobals.h>
#include "FT_NHD_43CTP_SHIELD.h"

/* Global object for FT801 Implementation */
FT801IMPL_SPI LCD(FT_CS_PIN,FT_PDN_PIN,FT_INT_PIN);
bool success = false;

void setup() {
  Serial.begin(9600);
  // Front valves
  pinMode(front.left.valve.up, OUTPUT);
  pinMode(front.right.valve.up, OUTPUT);
  pinMode(front.left.valve.down, OUTPUT);
  pinMode(front.right.valve.down, OUTPUT);
  // Rear valves
  pinMode(rear.left.valve.up, OUTPUT);
  pinMode(rear.right.valve.up, OUTPUT);
  pinMode(rear.left.valve.down, OUTPUT);
  pinMode(rear.right.valve.down, OUTPUT);

  /* Set the Display Enable pin*/   
	Serial.println("--Start Application--");
	if(BootupConfigure())
	{
    success = true;
	}
  	else
	{
		//error case - do not do any thing
	}
	Serial.println("--End Application--");
}

void loop() {
  // Get all sensor pressure data for front and rear airbags.
  if (success) {
    getPressureThread.check();
  }
  
}
