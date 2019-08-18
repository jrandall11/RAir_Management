/* air_to_preset
 * 
 * Inputs: preset
 * 
 * Outputs: Signal to air controller to air up car to mode specifications.
 */

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

  GetPressureReadings(&front, &rear);

  while (front.left.bag.sensor.pressure != frontPressure && 
         front.right.bag.sensor.pressure != frontPressure &&
         rear.left.bag.sensor.pressure != rearPressure &&
         rear.right.bag.sensor.pressure != rearPressure) {

          if (front.left.bag.sensor.pressure < frontPressure &&
               front.right.bag.sensor.pressure < frontPressure) {
                 
          }
  }

  
 }