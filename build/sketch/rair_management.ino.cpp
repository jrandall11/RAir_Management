#include <Arduino.h>
#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/rair_management.ino"
#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/rair_management.ino"
/*
  RAir Management

  A air management system for vehicle-equipped air-ride. This system aids in airing and maintaining air pressure
  in the air system. It also provides a way to air-up or down quickly depending on user input.

  The circuit:
  * A0 - Left front airbag pressure sensor.
  * A1 - Right front airbag pressure sensor.
  * A2 - Left rear airbag pressure sensor.
  * A3 - Right rear airbag pressure sensor.

  Created 27 July 2019
  By Joshua Randall
  Modified 27 July 2019
  By Joshua Randall

*/

#include <SPI.h>
#include <Wire.h>
#include <RAirGlobals.h>
#include "FT_NHD_43CTP_SHIELD.h"

/* Global object for FT801 Implementation */
FT801IMPL_SPI LCD(FT_CS_PIN,FT_PDN_PIN,FT_INT_PIN);
bool success = false;

#line 29 "/Users/joshrandall/Documents/Arduino/rair_management/rair_management.ino"
void setup();
#line 55 "/Users/joshrandall/Documents/Arduino/rair_management/rair_management.ino"
void loop();
#line 10 "/Users/joshrandall/Documents/Arduino/rair_management/air_to_preset.ino"
void AirToPreset(DrivingPresets preset);
#line 3 "/Users/joshrandall/Documents/Arduino/rair_management/boot_config.ino"
int16_t BootupConfigure();
#line 2 "/Users/joshrandall/Documents/Arduino/rair_management/display.ino"
void HelloWorld();
#line 3 "/Users/joshrandall/Documents/Arduino/rair_management/get_pressure.ino"
void GetPressure();
#line 13 "/Users/joshrandall/Documents/Arduino/rair_management/get_pressure_readings.ino"
void GetPressureReadings(Front *front, Rear *rear);
#line 14 "/Users/joshrandall/Documents/Arduino/rair_management/print_data.ino"
void PrintData(Front *front, Rear *rear);
#line 14 "/Users/joshrandall/Documents/Arduino/rair_management/print_sensor_data.ino"
void PrintSensorData(AirBag bag, int x, int y);
#line 13 "/Users/joshrandall/Documents/Arduino/rair_management/read_pressure_from_voltage.ino"
float ReadPressureFromVoltage(float voltage);
#line 11 "/Users/joshrandall/Documents/Arduino/rair_management/read_sensor_voltage.ino"
float ReadSensorVoltage(int circuit);
#line 14 "/Users/joshrandall/Documents/Arduino/rair_management/read_sensor_voltages.ino"
void ReadSensorVoltages(Front *front, Rear *rear);
#line 29 "/Users/joshrandall/Documents/Arduino/rair_management/rair_management.ino"
void setup() {
  Serial.begin(9600);
  // Front valves
  pinMode(front.left.valve.up, OUTPUT);
  pinMode(front.right.valve.up, OUTPUT);
  pinMode(front.left.valve.down, OUTPUT);
  pinMode(front.right.valve.down, OUTPUT);
  // Rear valves
  pinMode(rear.left.valve.up, OUTPUT);
  pinMode(rear.right.valve.up, OUTPUT);
  pinMode(rear.left.valve.down, OUTPUT);
  pinMode(rear.right.valve.down, OUTPUT);

  /* Set the Display Enable pin*/   
	Serial.println("--Start Application--");
	if(BootupConfigure())
	{
    success = true;
	}
  	else
	{
		//error case - do not do any thing
	}
	Serial.println("--End Application--");
}

void loop() {
  // Get all sensor pressure data for front and rear airbags.
  if (success) {
    getPressureThread.check();
  }
  
}

#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/air_to_preset.ino"
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
#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/boot_config.ino"
/* Api to bootup FT801, verify FT801 hardware and configure display/audio pins */
/* Returns 0 in case of success and 1 in case of failure */
int16_t BootupConfigure()
{
	uint32_t chipid = 0;
	LCD.Init(FT_DISPLAY_RESOLUTION);//configure the display to the WQVGA

	delay(20);//for safer side
	chipid = LCD.Read32(FT_ROM_CHIPID);
	
	/* Identify the chip */
	if(FT801_CHIPID != chipid)
	{
		Serial.print("Error in chip id read ");
		Serial.println(chipid,HEX);
		return 0;
	}
	
	/* Set the Display & audio pins */
	LCD.SetDisplayEnablePin(FT_DISPENABLE_PIN);
    LCD.SetAudioEnablePin(FT_AUDIOENABLE_PIN); 
	LCD.DisplayOn(); 	
	LCD.AudioOn();  		
	return 1;
}
#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/display.ino"
/* API to display Hello World string on the screen */
void HelloWorld()
{
	/* Change the below string for experimentation */
	const char Display_string[12] = "Hello World";
	
	/* Display list to display "Hello World" at the centre of display area */
	LCD.DLStart();//start the display list. Note DLStart and DLEnd are helper apis, Cmd_DLStart() and Display() can also be utilized.
	LCD.ColorRGB(0xFF,0xFF,0xFF);//set the color of the string to while color
	LCD.Cmd_Text(FT_DISPLAYWIDTH/2, FT_DISPLAYHEIGHT/2, 29, FT_OPT_CENTER, Display_string);//display "Hello World at the center of the screen using inbuilt font handle 29 "
	LCD.DLEnd();//end the display list
	LCD.Finish();//render the display list and wait for the completion of the DL
}
#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/get_pressure.ino"
#include <RAirGlobals.h>

void GetPressure() {
    GetPressureReadings(&front, &rear);
}

#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/get_pressure_readings.ino"
/* get_pressure_readings
 * 
 * Inputs:
 *    Front front
 *    Rear rear
 * Outputs:
 *    Nothing
 *  
 * Obtains all pressure readings from each airbag pressure sensor.
 */
#include <RAirGlobals.h>

void GetPressureReadings(Front *front, Rear *rear) {
  
  // Set old pressure values
  front->left.bag.sensor.old_pressure = front->left.bag.sensor.pressure;
  front->right.bag.sensor.old_pressure =front->right.bag.sensor.pressure;
  rear->left.bag.sensor.old_pressure = rear->left.bag.sensor.pressure;
  rear->right.bag.sensor.old_pressure = rear->right.bag.sensor.pressure;
  
  // Read voltage
  ReadSensorVoltages(front, rear);
  
  // Convert voltage to pressure
  front->left.bag.sensor.pressure   = (int)ReadPressureFromVoltage(front->left.bag.sensor.voltage);
  front->right.bag.sensor.pressure  = (int)ReadPressureFromVoltage(front->right.bag.sensor.voltage);
  rear->left.bag.sensor.pressure    = (int)ReadPressureFromVoltage(rear->left.bag.sensor.voltage);
  rear->right.bag.sensor.pressure   = (int)ReadPressureFromVoltage(rear->right.bag.sensor.voltage);

  // Print all sensor data
  PrintData(front, rear);
  
}

#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/print_data.ino"
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
    LCD.ClearColorRGB(0x3D0000);
    LCD.Clear();
    LCD.ColorRGB(0xA1,0x00,0x00);//set the color of the string to while color

    PrintSensorData(front->left.bag, 20, 20);
    PrintSensorData(front->right.bag, 450, 20);
    PrintSensorData(rear->left.bag, 20, 250);
    PrintSensorData(rear->right.bag, 450, 250);
    Serial.println();

    LCD.DLEnd();//end the display list
    LCD.Finish();//render the display list and wait for the completion of the DL

 }

#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/print_sensor_data.ino"
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

  /* Change the below string for experimentation */
	const char Display_string[12] = "Hello World";
	
	LCD.Cmd_Text(x, y, 29, FT_OPT_CENTER, pressure_buffer);//display "Hello World at the center of the screen using inbuilt font handle 29 "
  
}

#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/read_pressure_from_voltage.ino"
/* read_pressure_from_voltage
 * 
 * Inputs:
 *    voltage
 * Outputs:
 *    pressure
 *  
 * Converts voltage output from pressure sensor into psi.
 */

#include <RAirGlobals.h>

float ReadPressureFromVoltage(float voltage) {
  
  float rate = (MAX_SENSOR_PRESSURE - MIN_SENSOR_PRESSURE) / (MAX_SENSOR_VOLTAGE - MIN_SENSOR_VOLTAGE);
  return (rate * (voltage - MIN_SENSOR_VOLTAGE));
  
}

#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/read_sensor_voltage.ino"
/* read_sensor_voltage
 * 
 * Inputs:
 *    Sensor circuit
 * Outputs:
 *    Voltage
 *  
 * Returns voltage reading from particular circuit.
 */

float ReadSensorVoltage(int circuit) {
  
  return (analogRead(circuit) * (5.0 / 1023.0));
  
}

#line 1 "/Users/joshrandall/Documents/Arduino/rair_management/read_sensor_voltages.ino"
/* read_sensor_voltages
 * 
 * Inputs:
 *    Front front
 *    Rear rear
 * Outputs:
 *    Nothing
 *  
 * Reads voltage for all sensors.
 */

#include <RAirGlobals.h>

void ReadSensorVoltages(Front *front, Rear *rear) {
  
  front->left.bag.sensor.voltage  = ReadSensorVoltage(front->left.bag.sensor.circuit);
  front->right.bag.sensor.voltage = ReadSensorVoltage(front->right.bag.sensor.circuit);
  rear->left.bag.sensor.voltage   = ReadSensorVoltage(rear->left.bag.sensor.circuit);
  rear->right.bag.sensor.voltage  = ReadSensorVoltage(rear->right.bag.sensor.circuit);
  
}

