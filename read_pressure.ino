/* read_pressure
 * 
 * Inputs:
 *    voltage
 * Outputs:
 *    pressure
 *  
 * Converts voltage output from pressure sensor into psi.
 */

float ReadPressureFromVoltage(float voltage) {
  const float sensorMinV = 0.5;
  const float sensorMaxV = 4.5;
  const float sensorMinP = 0.0;
  const float sensorMaxP = 200.0;

  float rate = (sensorMaxP - sensorMinP) / (sensorMaxV - sensorMinV);
  return  (rate * voltage) - rate * sensorMinV;
}
