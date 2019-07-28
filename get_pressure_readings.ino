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
  
  // Read voltage
  ReadSensorVoltages(front, rear);
  
  // Convert voltage to pressure
  front->left.sensor.pressure = (int)ReadPressureFromVoltage(front->left.sensor.voltage);
  front->right.sensor.pressure = (int)ReadPressureFromVoltage(front->right.sensor.voltage);
  rear->left.sensor.pressure = (int)ReadPressureFromVoltage(rear->left.sensor.voltage);
  rear->right.sensor.pressure = (int)ReadPressureFromVoltage(rear->right.sensor.voltage);

  // Print all sensor data
  PrintData(front, rear);
  
}
