/* air_to_preset
 * 
 * Inputs: preset
 * 
 * Outputs: Signal to air controller to air up car to mode specifications.
 */

#include "jair_globals.h"

 void AirToPreset(DrivingPresets preset) {
  int frontPsi;
  int rearPsi;
  
  switch(preset) {
    case park:
      frontPsi = PARK_FRONT_PRESSURE;
      rearPsi = PARK_REAR_PRESSURE;
      break;
    case drive:
      frontPsi = DRIVE_FRONT_PRESSURE;
      rearPsi = DRIVE_REAR_PRESSURE;
      break;
    case sport:
      frontPsi = SPORT_FRONT_PRESSURE;
      rearPsi = SPORT_REAR_PRESSURE;
    default:
      break;
  }
 }
