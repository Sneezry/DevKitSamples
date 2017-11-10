/*
*  System time
*
*  Copyright (c) Microsoft Corporation
*  All rights reserved.
*  MIT License
*/

#include "Arduino.h";
#include "AZ3166WiFi.h";

time_t rawtime;
struct tm * currentTime;
char timeBuffer [80];
bool connected = false;

void setup()
{
    if (WiFi.begin() == WL_CONNECTED)
    {
        connected = true;
    }
    else
    {
        Serial.println("Cannot connect to ntp server.");
    }
}

void loop()
{
    if (!connected)
    {
        return;
    }

    time(&rawtime);
    currentTime = localtime(&rawtime);
    strftime(timeBuffer, 80, "%F %X", currentTime);

    Serial.println(timeBuffer);

    delay(1000);
}