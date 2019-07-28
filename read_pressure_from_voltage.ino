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
  return rate * (voltage - MIN_SENSOR_VOLTAGE);
  
}
