#include <Arduino.h>
#line 1 "/Users/joshrandall/Documents/Arduino/jair_management/jair_management.ino"
#line 1 "/Users/joshrandall/Documents/Arduino/jair_management/jair_management.ino"
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

#include <jair_globals.h>

#line 22 "/Users/joshrandall/Documents/Arduino/jair_management/jair_management.ino"
void setup();
#line 26 "/Users/joshrandall/Documents/Arduino/jair_management/jair_management.ino"
void loop();
#line 8 "/Users/joshrandall/Documents/Arduino/jair_management/air_to_p.ino"
void AirToPreset(DrivingPresets preset);
#line 12 "/Users/joshrandall/Documents/Arduino/jair_management/get_pressure_readings.ino"
void GetPressureReadings(Front *front, Rear *rear);
#line 12 "/Users/joshrandall/Documents/Arduino/jair_management/print_data.ino"
void PrintData(Front *front, Rear *rear);
#line 12 "/Users/joshrandall/Documents/Arduino/jair_management/print_sensor_data.ino"
void PrintSensorData(AirBag bag, int x, int y);
#line 11 "/Users/joshrandall/Documents/Arduino/jair_management/read_pressure_from_voltage.ino"
float ReadPressureFromVoltage(float voltage);
#line 11 "/Users/joshrandall/Documents/Arduino/jair_management/read_sensor_voltage.ino"
float ReadSensorVoltage(int circuit);
#line 12 "/Users/joshrandall/Documents/Arduino/jair_management/read_sensor_voltages.ino"
void ReadSensorVoltages(Front *front, Rear *rear);
#line 22 "/Users/joshrandall/Documents/Arduino/jair_management/jair_management.ino"
void setup() {
  Serial.begin(9600);
}

void loop() {
  // Get all sensor pressure data for front and rear airbags.
  GetPressureReadings(&front, &rear);
  delay(1000);
}

#line 1 "/Users/joshrandall/Documents/Arduino/jair_management/air_to_p.ino"
/* air_to_preset
 * 
 * Inputs: preset
 * 
 * Outputs: Signal to air controller to air up car to mode specifications.
 */

 void AirToPreset(DrivingPresets preset) {

  int frontPressure;
  int rearPressure;
  
  switch(preset) {
    case park:
      frontPressure = PARK_FRONT_PRESSURE;
      rearPressure = PARK_REAR_PRESSURE;
      break;
    case drive:
      frontPressure = DRIVE_FRONT_PRESSURE;
      rearPressure = DRIVE_REAR_PRESSURE;
      break;
    case sport:
      frontPressure = SPORT_FRONT_PRESSURE;
      rearPressure = SPORT_REAR_PRESSURE;
    case pothole:
      frontPressure = POTHOLE_FRONT_PRESSURE;
      rearPressure = POTHOLE_REAR_PRESSURE;
    case maximum_height:
      frontPressure = MAXIMUM_FRONT_PRESSURE;
      rearPressure = MAXIMUM_REAR_PRESSURE;
    default:
      break;
  }

  GetPressureReadings(&front, &rear);

  while (front.left.bag.sensor.pressure != frontPressure && 
         front.right.bag.sensor.pressure != frontPressure &&
         rear.left.bag.sensor.pressure != rearPressure &&
         rear.right.bag.sensor.pressure != rearPressure) {

          if (front.left.bag.sensor.pressure < frontPressure &&
               front.right.bag.sensor.pressure < frontPressure) {
                 
          }
  }

  
 }
#line 1 "/Users/joshrandall/Documents/Arduino/jair_management/get_pressure_readings.ino"
/* get_pressure_readings
 * 
 * Inputs:
 *    Front front
 *    Rear rear
 * Outputs:
 *    Nothing
 *  
 * Obtains all pressure readings from each airbag pressure sensor.
 */

void GetPressureReadings(Front *front, Rear *rear) {
  
  // Set old pressure values
  front->left.bag.sensor.old_pressure = front->left.bag.sensor.pressure;
  front->right.bag.sensor.old_pressure =front->right.bag.sensor.pressure;
  rear->left.bag.sensor.old_pressure = rear->left.bag.sensor.pressure;
  rear->right.bag.sensor.old_pressure = rear->right.bag.sensor.pressure;
  
  // Read voltage
  ReadSensorVoltages(front, rear);
  
  // Convert voltage to pressure
  front->left.bag.sensor.pressure   = (int)ReadPressureFromVoltage(front->left.bag.sensor.voltage);
  front->right.bag.sensor.pressure  = (int)ReadPressureFromVoltage(front->right.bag.sensor.voltage);
  rear->left.bag.sensor.pressure    = (int)ReadPressureFromVoltage(rear->left.bag.sensor.voltage);
  rear->right.bag.sensor.pressure   = (int)ReadPressureFromVoltage(rear->right.bag.sensor.voltage);

  // Print all sensor data
  PrintData(front, rear);
  
}

#line 1 "/Users/joshrandall/Documents/Arduino/jair_management/print_data.ino"
/* print_data
 * 
 * Inputs:
 *    Front front
 *    Rear rear
 * Outputs:
 *    nothing
 *  
 * Takes sensor data for front and rear and prints it to console.
 */

 void PrintData(Front *front, Rear *rear) {
  
  PrintSensorData(front->left.bag, 5, 20);
  PrintSensorData(front->right.bag, 150, 20);
  PrintSensorData(rear->left.bag, 5, 250);
  PrintSensorData(rear->right.bag, 150, 250);
  Serial.println();
  
 }

#line 1 "/Users/joshrandall/Documents/Arduino/jair_management/print_sensor_data.ino"
/* print_sensor_data
 * 
 * Inputs:
 *    corner name,
 *    bag pressure
 * Outputs:
 *    nothing
 *  
 * Takes sensor data and prints it to console.
 */

void PrintSensorData(AirBag bag, int x, int y) {
  
  Serial.print((char *)bag._Name);
  Serial.print(": ");
  Serial.print(bag.sensor.pressure);
  Serial.println(" psi");
  
}

#line 1 "/Users/joshrandall/Documents/Arduino/jair_management/read_pressure_from_voltage.ino"
/* read_pressure_from_voltage
 * 
 * Inputs:
 *    voltage
 * Outputs:
 *    pressure
 *  
 * Converts voltage output from pressure sensor into psi.
 */

float ReadPressureFromVoltage(float voltage) {
  
  float rate = (MAX_SENSOR_PRESSURE - MIN_SENSOR_PRESSURE) / (MAX_SENSOR_VOLTAGE - MIN_SENSOR_VOLTAGE);
  return (rate * (voltage - MIN_SENSOR_VOLTAGE));
  
}

#line 1 "/Users/joshrandall/Documents/Arduino/jair_management/read_sensor_voltage.ino"
/* read_sensor_voltage
 * 
 * Inputs:
 *    Sensor circuit
 * Outputs:
 *    Voltage
 *  
 * Returns voltage reading from particular circuit.
 */

float ReadSensorVoltage(int circuit) {
  
  return (analogRead(circuit) * (5.0 / 1023.0));
  
}

#line 1 "/Users/joshrandall/Documents/Arduino/jair_management/read_sensor_voltages.ino"
/* read_sensor_voltages
 * 
 * Inputs:
 *    Front front
 *    Rear rear
 * Outputs:
 *    Nothing
 *  
 * Reads voltage for all sensors.
 */

void ReadSensorVoltages(Front *front, Rear *rear) {
  
  front->left.bag.sensor.voltage  = ReadSensorVoltage(front->left.bag.sensor.circuit);
  front->right.bag.sensor.voltage = ReadSensorVoltage(front->right.bag.sensor.circuit);
  rear->left.bag.sensor.voltage   = ReadSensorVoltage(rear->left.bag.sensor.circuit);
  rear->right.bag.sensor.voltage  = ReadSensorVoltage(rear->right.bag.sensor.circuit);
  
}

