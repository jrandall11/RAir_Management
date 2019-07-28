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
  // Read voltage
  lF.sensor.voltage = ReadSensorVoltage(lF.sensor.circuit);
  rF.sensor.voltage = ReadSensorVoltage(rF.sensor.circuit);
  lR.sensor.voltage = ReadSensorVoltage(lR.sensor.circuit);
  rR.sensor.voltage = ReadSensorVoltage(rR.sensor.circuit);

  // Convert voltage to pressure
  lF.sensor.pressure = (int)ReadPressureFromVoltage(lF.sensor.voltage);
  rF.sensor.pressure = (int)ReadPressureFromVoltage(rF.sensor.voltage);
  lR.sensor.pressure = (int)ReadPressureFromVoltage(lR.sensor.voltage);
  rR.sensor.pressure = (int)ReadPressureFromVoltage(rR.sensor.voltage);

  // Print data
  printSensorData((char *)lF.bagName, lF.sensor.pressure);
  printSensorData((char *)rF.bagName, rF.sensor.pressure);
  printSensorData((char *)lR.bagName, lR.sensor.pressure);
  printSensorData((char *)rR.bagName, rR.sensor.pressure);
  Serial.println();
  
  delay(1000);
}
