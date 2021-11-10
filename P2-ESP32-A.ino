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
void BPM(void); // Prototipo de función encargada de enviar el valor BPM a la tiva C mediante comunicación USART.
void leerSensor(void); // Prototipo de función encargada de leer el valor BPM del sensor. 

//**********************************************************************************************************************
// Variables Globales
//**********************************************************************************************************************

String estadoBoton = ""; // Variable con la cual se recibe la instrucción por parte de la tiva c para enviar el valor BPM
int estado = 0;
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

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
  //Función que permite leer BPM consecuitvamente, además permite determinar el BPM y el promedio de BPM. 
   long irValue = particleSensor.getIR();
    if (checkForBeat(irValue) == true)
    {
      //Leer latido del corazón. 
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20)
      {
        rates[rateSpot++] = (byte)beatsPerMinute; //Almacenar el valor en la matriz
        rateSpot %= RATE_SIZE; //Wrap variable

        //Tomar el promedio del BPM
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }

    Serial.print("Promedio de BPM: ");
    Serial.print(beatAvg);

   // Condición que identific
    if (irValue < 50000)
    Serial.print(" Coloque su dedo índice");
    Serial.println();
}
