/*
*  Blink LED
*
*  Copyright (c) Microsoft Corporation
*  All rights reserved.
*  MIT License
*/

#include "Arduino.h";

void setup()
{
    pinMode(LED_USER, OUTPUT);
}

void loop()
{
    digitalWrite(LED_USER, LOW);
    delay(500);
    digitalWrite(LED_USER, HIGH);
    delay(500);
}