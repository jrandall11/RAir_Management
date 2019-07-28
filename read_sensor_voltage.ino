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

  return analogRead(circuit) * (5.0 / 1023.0);
  
}
