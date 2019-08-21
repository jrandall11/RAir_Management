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

#include <RAirGlobals.h>

 void PrintData(Front *front, Rear *rear) {
  
  /* Display list to display "Hello World" at the centre of display area */
    LCD.DLStart();//start the display list. Note DLStart and DLEnd are helper apis, Cmd_DLStart() and Display() can also be utilized.
    LCD.ClearColorRGB(0x3D0000);// Set background to Red.
    LCD.Clear();
    LCD.ColorRGB(0xA1,0x00,0x00);//set the color of the string to Red color

    PrintSensorData(front->left.bag, 20, 20);
    PrintSensorData(front->right.bag, 450, 20);
    PrintSensorData(rear->left.bag, 20, 250);
    PrintSensorData(rear->right.bag, 450, 250);
    Serial.println();

    LCD.DLEnd();//end the display list
    LCD.Finish();//render the display list and wait for the completion of the DL

 }
