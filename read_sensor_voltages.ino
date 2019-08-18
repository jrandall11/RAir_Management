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

#include <RAirGlobals.h>

void ReadSensorVoltages(Front *front, Rear *rear) {
  
  front->left.bag.sensor.voltage  = ReadSensorVoltage(front->left.bag.sensor.circuit);
  front->right.bag.sensor.voltage = ReadSensorVoltage(front->right.bag.sensor.circuit);
  rear->left.bag.sensor.voltage   = ReadSensorVoltage(rear->left.bag.sensor.circuit);
  rear->right.bag.sensor.voltage  = ReadSensorVoltage(rear->right.bag.sensor.circuit);
  
}
