/* print_data
 * 
 * Inputs:
 *    corner name,
 *    bag pressure
 * Outputs:
 *    nothing
 *  
 * Takes sensor data and prints it to console.
 */

void printSensorData(char *cornerName, int psi) {
  Serial.print(cornerName);
  Serial.print(": ");
  Serial.print(psi);
  Serial.println(" psi");
}
