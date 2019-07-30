/*
  jAir Management

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

#include "jair_globals.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Get all sensor pressure data for front and rear airbags.
  GetPressureReadings(&front, &rear);
  delay(1000);
}
