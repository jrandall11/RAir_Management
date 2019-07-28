/* print_data
 * 
 * Inputs:
 *    Front front
 *    Rear rear
 * Outputs:
 *    nothing
 *  
 * Takes sensor data for front and rear and prints it to console.
 */

 void PrintData(Front *front, Rear *rear) {
  
  PrintSensorData((char *)front->left._Name, front->left.sensor.pressure);
  PrintSensorData((char *)front->right._Name, front->right.sensor.pressure);
  PrintSensorData((char *)rear->left._Name, rear->left.sensor.pressure);
  PrintSensorData((char *)rear->right._Name, rear->right.sensor.pressure);
  Serial.println();
  
 }
