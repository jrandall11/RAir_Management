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
  
  front->left.sensor.voltage = ReadSensorVoltage(front->left.sensor.circuit);
  front->right.sensor.voltage = ReadSensorVoltage(front->right.sensor.circuit);
  rear->left.sensor.voltage = ReadSensorVoltage(rear->left.sensor.circuit);
  rear->right.sensor.voltage = ReadSensorVoltage(rear->right.sensor.circuit);
  
}
