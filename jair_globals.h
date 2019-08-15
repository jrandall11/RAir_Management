/* jair_globals
 * 
 * predefined types for application.
 */

#ifndef jair_globals_h
#define jair_globals_h
#endif

// LCD
UTFT myGLCD(ILI9341_16, 38,39,40,41);
URTouch  myTouch( 6, 5, 4, 3, 2);

// Sensor Properties
const float MIN_SENSOR_VOLTAGE = 0.5;
const float MAX_SENSOR_VOLTAGE = 4.5;
const float MIN_SENSOR_PRESSURE = 0.0;
const float MAX_SENSOR_PRESSURE = 200.0;

// Air Pressure Presets
const int PARK_FRONT_PRESSURE = 0;
const int PARK_REAR_PRESSURE = 20;

const int DRIVE_FRONT_PRESSURE = 70;
const int DRIVE_REAR_PRESSURE = 95;

const int SPORT_FRONT_PRESSURE = 60;
const int SPORT_REAR_PRESSURE = 75;

const int POTHOLE_FRONT_PRESSURE = 90;
const int POTHOLE_REAR_PRESSURE = 110;

const int MAXIMUM_FRONT_PRESSURE = 124;
const int MAXIMUM_REAR_PRESSURE = 124;

// Air Ride Mode Presets
typedef enum {
  park,
  drive,
  sport,
  pothole,
  maximum
} DrivingPresets;

// Sensor
struct PressureSensor {
  /* 200 PSI eBay Pressure Sensor
   *  Info:
   *    Input: 0-200 psi
   *    Output: 0.5V~4.5V linear voltage output. 0 psi outputs 0.5V, 100 psi outputs 2.5V, and 200 psi outputs 4.5V
   *    Working Temperature: -40~+125℃
   *    Accuracy: ±1%FS
   *    Thread: 1/8"-27 NPT
   *    Overload Capacity: 2 times of rated pressure
   *    Pressure Medium: Oil, gas and water which is compatible with 316L stainless steel
   *    Load Resistance: ≤(supply power-6.5V/0.02A)Ω
   *    Long-term Stability: ± 0.2%FS/year
   *    Temperature Effect on Zero: Typical: ±0.02%FS/℃; Maximum: ±0.05%FS/℃
   *    Temperature Effect on Sensitivity: Typical: ±0.02%FS/℃; Maximum: ±0.05%FS/℃
   *    Shock Resistance: 100g
   *    Anti-Shock: ≤±0.01%FS(X,Y,Z axes, 200Hz/g)
   *    Response Time: ≤1ms
   *    Insulation Resistance: >100mΩ 500VDC
   *    Explosion-proof Class: ExiaTTCT6
   *    Electromagnetism Compatibility: EN50081-1; EN50082-2; IEC6 1000-4-3
   *    Wiring Connector: Water sealed quick disconnect. Mating connector and wire harness (pigtail) is included.
   *    Wiring: Red for IN+; Black for GND; Green for OUT.
   */
  const int circuit;
  int pressure;
  int old_pressure;
  float voltage;
};

// Air Bags
struct AirBag {
  /* AirLift Suspension
   *  Info:
   *    Input: 0-125 psi
   *    Max supported pressure: 125 psi
   */
  const char *_Name;
  PressureSensor sensor;
};

struct Front {
  struct Left {
    AirBag bag;
  } left;
  struct Right {
    AirBag bag;
  } right;
} front {{"Driver Front", {A0, 0, 0}}, 
         {"Passenger Front", {A1, 0, 0}}};

struct Rear {
  struct Left {
    AirBag bag;
  } left;
  struct Right {
    AirBag bag;
  } right;
} rear {{"Driver Rear", {A2, 0, 0}}, 
        {"Pasenger Rear", {A3, 0, 0}}};

// Prototypes
float ReadSensorVoltage(int circuit);
void PrintSensorData(AirBag bag, int x, int y);
void PrintData(Front *front, Rear *rear);
float ReadSensorVoltage(int circuit);
float ReadPressureFromVoltage(float voltage);
void ReadSensorVoltages(Front *front, Rear *rear);



