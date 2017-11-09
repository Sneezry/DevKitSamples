/*
*  Connect WiFi
*  Reference API: https://microsoft.github.io/azure-iot-developer-kit/docs/apis/wifi/
*
*  Copyright (c) Microsoft Corporation
*  All rights reserved.
*  MIT License
*/

#include "Arduino.h";
#include "AZ3166WiFi.h";

void setup()
{
    if (WiFi.begin() == WL_CONNECTED)
    {
        IPAddress ip = WiFi.localIP();

        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());
        Serial.print("IP address: ");
        Serial.println(ip.get_address());
    }
    else
    {
        Serial.println("No internet connection.");
    }
}

void loop()
{

}