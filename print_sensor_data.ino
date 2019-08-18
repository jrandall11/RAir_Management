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

#include <RAirGlobals.h>

void PrintSensorData(AirBag bag, int x, int y) {
  
  Serial.print((char *)bag._Name);
  Serial.print(": ");
  Serial.print(bag.sensor.pressure);
  Serial.println(" psi");
  
}
