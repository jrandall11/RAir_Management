/* air_to_preset
 * 
 * Inputs: preset
 * 
 * Outputs: Signal to air controller to air up car to mode specifications.
 */

#include <RAirGlobals.h>

 void AirToPreset(DrivingPresets preset) {

  int frontPressure;
  int rearPressure;
  
  switch(preset) {
    case park:
      frontPressure = PARK_FRONT_PRESSURE;
      rearPressure = PARK_REAR_PRESSURE;
      break;
    case drive:
      frontPressure = DRIVE_FRONT_PRESSURE;
      rearPressure = DRIVE_REAR_PRESSURE;
      break;
    case sport:
      frontPressure = SPORT_FRONT_PRESSURE;
      rearPressure = SPORT_REAR_PRESSURE;
    case pothole:
      frontPressure = POTHOLE_FRONT_PRESSURE;
      rearPressure = POTHOLE_REAR_PRESSURE;
    case maximum_height:
      frontPressure = MAXIMUM_FRONT_PRESSURE;
      rearPressure = MAXIMUM_REAR_PRESSURE;
    default:
      break;
  }

  getPressureThread.setInterval(250);
  getPressureThread.check();
  while (front.left.bag.sensor.pressure != frontPressure && 
         front.right.bag.sensor.pressure != frontPressure &&
         rear.left.bag.sensor.pressure != rearPressure &&
         rear.right.bag.sensor.pressure != rearPressure) {

          // Adjust Front Left Pressure
          if (front.left.bag.sensor.pressure < frontPressure) {
            digitalWrite(front.left.valve.up, HIGH);
            digitalWrite(front.left.valve.down, LOW);
          }
          else if (front.left.bag.sensor.pressure > frontPressure) {
            digitalWrite(front.left.valve.up, LOW);
            digitalWrite(front.left.valve.down, HIGH);
          }
          else {
            digitalWrite(front.left.valve.up, LOW);
            digitalWrite(front.left.valve.down, LOW);
          }

          // Adjust Front Right Pressure
          if (front.right.bag.sensor.pressure < frontPressure) {
            digitalWrite(front.right.valve.up, HIGH);
            digitalWrite(front.right.valve.down, LOW);
          }
          else if (front.right.bag.sensor.pressure > frontPressure) {
            digitalWrite(front.right.valve.up, LOW);
            digitalWrite(front.right.valve.down, HIGH);
          }
          else {
            digitalWrite(front.right.valve.up, LOW);
            digitalWrite(front.right.valve.down, LOW);
          }

          // Adjust Rear Left Pressure
          if (rear.left.bag.sensor.pressure < rearPressure) {
            digitalWrite(rear.left.valve.up, HIGH);
            digitalWrite(rear.left.valve.down, LOW);
          }
          else if (rear.left.bag.sensor.pressure > rearPressure) {
            digitalWrite(rear.left.valve.up, LOW);
            digitalWrite(rear.left.valve.down, HIGH);
          }
          else {
            digitalWrite(rear.left.valve.up, LOW);
            digitalWrite(rear.left.valve.down, LOW);
          }

          // Adjust Rear Right Pressure
          if (rear.right.bag.sensor.pressure < rearPressure) {
            digitalWrite(rear.right.valve.up, HIGH);
            digitalWrite(rear.right.valve.down, LOW);
          }
          else if (rear.right.bag.sensor.pressure > rearPressure) {
            digitalWrite(rear.right.valve.up, LOW);
            digitalWrite(rear.right.valve.down, HIGH);
          }
          else {
            digitalWrite(rear.right.valve.up, LOW);
            digitalWrite(rear.right.valve.down, LOW);
          }

          getPressureThread.check();
  }
  getPressureThread.setInterval(1000);
 }