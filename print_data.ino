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
  
  PrintSensorData((char *)front->left.bag._Name,  front->left.bag.sensor.pressure);
  PrintSensorData((char *)front->right.bag._Name, front->right.bag.sensor.pressure);
  PrintSensorData((char *)rear->left.bag._Name,   rear->left.bag.sensor.pressure);
  PrintSensorData((char *)rear->right.bag._Name,  rear->right.bag.sensor.pressure);
  Serial.println();
  
 }
