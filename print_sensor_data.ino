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

#include "jair_globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charToInt(char d)
{
 char str[2];
 str[0] = d;
 str[1] = '\0';
 return (int)strtol(str, NULL, 10);
}

void PrintSensorData(AirBag bag, int x, int y) {
  char old_pressure_buffer[4];
  itoa(bag.sensor.old_pressure, old_pressure_buffer, 10);
  int old_size = strlen(old_pressure_buffer);

  char new_pressure_buffer[4];
  itoa(bag.sensor.pressure, new_pressure_buffer, 10);
  int new_size = strlen(new_pressure_buffer);
  int font_size = myGLCD.getFontXsize();
  
  if (new_size > old_size) {
    for (int i=0; i<new_size; i++) {
      x += font_size;
      if(i < old_size){
        if(old_pressure_buffer[i]!=new_pressure_buffer[i]){
          if (new_pressure_buffer[i] == '-'){
            myGLCD.print("-", x, y);
          }
          else {
            myGLCD.printNumI(charToInt(new_pressure_buffer[i]), x, y);
          }
        }
      }
      else {
        myGLCD.printNumI(charToInt(new_pressure_buffer[i]), x, y);
      }
    }
  }
  else {
    for (int i=0; i<old_size; i++) {
      x += font_size;
      if (i < new_size){
        if(old_pressure_buffer[i]!=new_pressure_buffer[i]){
          if (new_pressure_buffer[i] == '-'){
            myGLCD.print("-", x, y);
          }
          else {
            myGLCD.printNumI(charToInt(new_pressure_buffer[i]), x, y);
          }
        }
      }
      else{
        myGLCD.print(" ", x, y);
      }
    }
  }

  Serial.print(old_pressure_buffer);
  Serial.print(":");
  Serial.print(new_pressure_buffer);
  Serial.print(":");
  Serial.print((char *)bag._Name);
  Serial.print(": ");
  Serial.print(bag.sensor.pressure);
  Serial.println(" psi");
  
}
