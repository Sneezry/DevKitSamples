#include "Arduino.h";

void setup()
{
  pinMode(PWM_OUT, OUTPUT); // Pin shared with onboard green LED
  Serial.begin(9600);
}

void loop()
{
  // Onboard green LED gets brighter
  for (int i = 1; i < 50; i++)
  {
    analogWrite(PWM_OUT, i);

    Serial.print("PWM Value:");
    Serial.println(i);

    delay(20);
  }

  // Onboard green LED gets dimmer
  for (int i = 50; i > 1; i--)
  {
    analogWrite(PWM_OUT, i);

    Serial.print("PWM Value:");
    Serial.println(i);

    delay(20);
  }
}
