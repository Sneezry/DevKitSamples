/*
*  Read humidity & temperature sensor data
*
*  Copyright (c) Microsoft Corporation
*  All rights reserved.
*  MIT License
*/

#include "Arduino.h";
#include "HTS221Sensor.h"

DevI2C *extI2C;
HTS221Sensor *htSensor;
float temperature;
float humidity;

void setup()
{
    extI2C = new DevI2C(D14, D15);
    htSensor = new HTS221Sensor(*extI2C);
    htSensor->init(NULL);
}

void loop()
{
    htSensor->reset();
    htSensor->getTemperature(&temperature);
    htSensor->getHumidity(&humidity);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.println(humidity);

    delay(5000);
}