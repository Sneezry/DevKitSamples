/*
*  Print log messages to seial port
*
*  Copyright (c) Microsoft Corporation
*  All rights reserved.
*  MIT License
*/

#include "Arduino.h";

int count = 0;

void setup()
{
    Serial.println("Hello from DevKit.");
}

void loop()
{
    Serial.print("ping: ");
    Serial.println(count++);

    delay(1000);
}