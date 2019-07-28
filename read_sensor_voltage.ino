/* read_sensor_voltage
 * 
 * Inputs:
 *    Sensor circuit
 * Outputs:
 *    Voltage
 *  
 * Reads circuit and returns voltage.
 */

float ReadSensorVoltage(int sensor) {
  return analogRead(sensor) * (5.0 / 1023.0);
}
