/*
*  RGB Light
*  Reference API: https://microsoft.github.io/azure-iot-developer-kit/docs/apis/led/
*
*  Copyright (c) Microsoft Corporation
*  All rights reserved.
*  MIT License
*/

#include "Arduino.h";
#include "RGB_LED.h";

static RGB_LED rgbLed;

int colorIndex = 0;
int intensity = 0;
int step = 1;

void setup()
{
    
}

void loop()
{
    intensity += step;

    if (intensity == 255)
    {
        step = -1;
    }

    if (intensity == 0)
    {
        step = 1;
        colorIndex++;
        colorIndex %= 3;
    }

    switch(colorIndex)
    {
        case 0:
            rgbLed.setColor(intensity, 0, 0);
            break;
        case 1:
            rgbLed.setColor(0, intensity, 0);
            break;
        case 2:
            rgbLed.setColor(0, 0, intensity);
            break;
    }

    delay(10);
}