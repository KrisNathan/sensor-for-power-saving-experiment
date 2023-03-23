#include <PZEM004Tv30.h>

/* Hardware Serial2 is only available on certain boards.
 * For example the Arduino MEGA 2560
 */
#if defined(ESP32)
PZEM004Tv30 pzem(Serial2, 16, 17);
#else
PZEM004Tv30 pzem(Serial2);
#endif

// turns off after x seconds of inactivity
const int CUT_OFF_VALUE = 60; 

// add x seconds worth of activity
const int TRIGGER_VALUE = 10;

void setup()
{
  Serial.begin(9600);

  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(27, INPUT);

  digitalWrite(33, LOW);
  digitalWrite(32, LOW);
  // Uncomment in order to reset the internal energy counter
  // pzem.resetEnergy()
}

void print_meter_readings()
{
  float voltage = pzem.voltage();     // V
  float current = pzem.current();     // A
  float power = pzem.power();         // W
  float energy = pzem.energy();       // kWh
  float frequency = pzem.frequency(); // Hz
  float pf = pzem.pf();

  if (isnan(voltage) || isnan(current) || isnan(power) || isnan(energy) || isnan(frequency) || isnan(pf))
    return;

  Serial.printf("{\"voltage\":%f,\"current\":%f,\"power\":%f,\"energy\":%f,\"frequency\":%f,\"pf\":%f}\n", voltage, current, power, energy, frequency, pf);
  // Serial.printf("[%f,%f,%f,%f,%f,%f]\n", voltage, current, power, energy, frequency, pf);
}



int counter = 0;

void loop()
{
  delay(1000);
  // Serial.println(counter);
  if (digitalRead(27) == HIGH)
  {
    counter+=TRIGGER_VALUE;
  }
  else
  {
    counter--;
  }

  if (counter <= 0)
  {
    counter = 0;

    print_meter_readings();
    digitalWrite(33, HIGH);
    print_meter_readings();
  }
  else
  {
    print_meter_readings();
    digitalWrite(33, LOW);
    print_meter_readings();

    if (counter > CUT_OFF_VALUE)
      counter = CUT_OFF_VALUE;
  }
}

// void check()
// {
//   // Read the data from the sensor
//   float voltage = pzem.voltage();
//   float current = pzem.current();
//   float power = pzem.power();
//   float energy = pzem.energy();
//   float frequency = pzem.frequency();
//   float pf = pzem.pf();

//   // Check if the data is valid
//   if (isnan(voltage) || isnan(current) || isnan(power) || isnan(energy) || isnan(frequency) || isnan(pf))
//   {
//     Serial.println("Error reading voltage");
//   }
//   else if (isnan(current))
//   {
//     Serial.println("Error reading current");
//   }
//   else if (isnan(power))
//   {
//     Serial.println("Error reading power");
//   }
//   else if (isnan(energy))
//   {
//     Serial.println("Error reading energy");
//   }
//   else if (isnan(frequency))
//   {
//     Serial.println("Error reading frequency");
//   }
//   else if (isnan(pf))
//   {
//     Serial.println("Error reading power factor");
//   }
//   else
//   {
//     // Print the values to the Serial console
//     Serial.print("Voltage: ");
//     Serial.print(voltage);
//     Serial.println("V");
//     Serial.print("Current: ");
//     Serial.print(current);
//     Serial.println("A");
//     Serial.print("Power: ");
//     Serial.print(power);
//     Serial.println("W");
//     Serial.print("Energy: ");
//     Serial.print(energy, 3);
//     Serial.println("kWh");
//     Serial.print("Frequency: ");
//     Serial.print(frequency, 1);
//     Serial.println("Hz");
//     Serial.print("PF: ");
//     Serial.println(pf);
//   }
// }
