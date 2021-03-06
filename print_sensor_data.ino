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
  
  char pressure_buffer[4];
  itoa(bag.sensor.pressure, pressure_buffer, 10);

  Serial.print((char *)bag._Name);
  Serial.print(": ");
  Serial.print(bag.sensor.pressure);
  Serial.println(" psi");
	
	LCD.Cmd_Text(x, y, 25, FT_OPT_CENTER, pressure_buffer);//display pressure values.
  
}
