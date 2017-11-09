/*
*  Press button
*
*  Copyright (c) Microsoft Corporation
*  All rights reserved.
*  MIT License
*/

#include "Arduino.h";

int buttonAStatus = HIGH;
int buttonBStatus = HIGH;

void setup()
{
    pinMode(USER_BUTTON_A, INPUT);
    pinMode(USER_BUTTON_B, INPUT);
}

void loop()
{
    if (digitalRead(USER_BUTTON_A) != buttonAStatus)
    {
        if (buttonAStatus == HIGH)
        {
            Serial.println("Button A pressed.");
        }
        else
        {
            Serial.println("Button A released.");
        }

        buttonAStatus = digitalRead(USER_BUTTON_A);
    }

    if (digitalRead(USER_BUTTON_B) != buttonBStatus)
    {
        if (buttonBStatus == HIGH)
        {
            Serial.println("Button B pressed.");
        }
        else
        {
            Serial.println("Button B released.");
        }

        buttonBStatus = digitalRead(USER_BUTTON_B);
    }

    delay(100);
}