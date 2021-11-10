//********************************************************************************
// Universidad del Valle de Guatemala
// BE3015: Electrnónica Digital 2
// José David Méndez 19380
// Proyecto No.2 ESP32
//********************************************************************************

//**********************************************************************************************************************
// Librerías
//**********************************************************************************************************************
#include <Arduino.h>
// Llamado de librerias para poder configurar el sensor MAX30102/30105
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
MAX30105 particleSensor;
//**********************************************************************************************************************
// Prototipo de Funciones
//**********************************************************************************************************************
//**********************************************************************************************************************
// Variables Globales
//**********************************************************************************************************************
//**********************************************************************************************************************
// Configuracion
//**********************************************************************************************************************
void setup()
{
  Serial.begin(115200); // Velocidad con la que se trabja la comunicación serial del canal 0.
  Serial2.begin(115200);  // Velocidad con la que se trabaja la comunicación serial del canal 2.
  
  //------------------------ Configuración del Sensor de ritmo cárdiaco ------------------------
  Serial.println("Initializing...");
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  //---------------------------------------------------------------------------------------------
}
//**********************************************************************************************************************
// LOOP
//**********************************************************************************************************************
void loop()
}
//**********************************************************************************************************************
// Fuinciones
//**********************************************************************************************************************
void BPM(void)
void leerSensor() {
