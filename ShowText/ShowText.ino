/*
*  Show text on DevKit OLED display
*  Reference API: https://microsoft.github.io/azure-iot-developer-kit/docs/apis/display/
*
*  Copyright (c) Microsoft Corporation
*  All rights reserved.
*  MIT License
*/

#include "Arduino.h";
#include "OledDisplay.h";

void setup()
{
    Screen.clean();
    Screen.print("Hello");
    Screen.print(1, "  World!");
    Screen.print(2, "This is a very long instence.", true);
}

void loop()
{

}