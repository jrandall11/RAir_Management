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
  
  PrintSensorData(front->left.bag, 5, 20);
  PrintSensorData(front->right.bag, 150, 20);
  PrintSensorData(rear->left.bag, 5, 250);
  PrintSensorData(rear->right.bag, 150, 250);
  Serial.println();
  
 }
