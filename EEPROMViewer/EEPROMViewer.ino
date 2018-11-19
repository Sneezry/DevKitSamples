#include "Arduino.h"
#include "EEPROMInterface.h"
#include "EEPROM.h"

enum Config {
  ssid,
  pwd,
  iothub,
  uds
};

int buttonAStatus = HIGH;
int buttonBStatus = HIGH;
int lineOffset = 0;
int maxLine = 0;

char* eepromString = (char*)malloc(DPS_UDS_MAX_LEN + WIFI_SSID_MAX_LEN + WIFI_PWD_MAX_LEN + AZ_IOT_HUB_MAX_LEN + 64);

bool readEEPROM(Config config, uint8_t * dataBuff) {
  int buffSize, dataZoneIndex;
  uint8_t* configName = (uint8_t*)malloc(25);

  switch(config) {
    case ssid:
      configName = (uint8_t*)"WiFi-SSID";
      buffSize = WIFI_SSID_MAX_LEN;
      dataZoneIndex = WIFI_SSID_ZONE_IDX;
      break;
    case pwd:
      configName = (uint8_t*)"WiFi-PWD";
      buffSize = WIFI_PWD_MAX_LEN;
      dataZoneIndex = WIFI_PWD_ZONE_IDX;
      break;
    case iothub:
      configName = (uint8_t*)"IoT Hub Connection String";
      buffSize = AZ_IOT_HUB_MAX_LEN;
      dataZoneIndex = AZ_IOT_HUB_ZONE_IDX;
      break;
    case uds:
      configName = (uint8_t*)"UDS String";
      buffSize = DPS_UDS_MAX_LEN;
      dataZoneIndex = DPS_UDS_ZONE_IDX;
      break;
    default:
      dataBuff = (uint8_t*)"Unknown config";
      return false;
  }

  EEPROMInterface eeprom;
  int ret = eeprom.read(dataBuff, buffSize, 0x00, dataZoneIndex);

  if (ret < 0)
  {
    dataBuff = (uint8_t*)"Inaccessible";
    return false;
  }
  else if (ret == 0)
  {
    dataBuff = (uint8_t*)"Empty";
    return false;
  }
  else if (ret <= buffSize)
  {
    dataBuff[ret] = 0;
  } else {
    dataBuff[buffSize] = 0;
  }

  return true;
}

void wrapIntoLines(uint8_t* dataBuff, int buffSize, uint8_t* newDataBuff, int lineLen) {
  int buffIndex = 0;
  int currentLineChars = 0;
  int newDataBuffIndex = 0;
  
  while(buffIndex <= buffSize && dataBuff[buffIndex] != 0)
  {
    if (currentLineChars >= lineLen) 
    {
      newDataBuff[newDataBuffIndex] = '\r';
      newDataBuffIndex++;
      newDataBuff[newDataBuffIndex] = '\n';
      newDataBuffIndex++;
      currentLineChars = 0;
    }
    newDataBuff[newDataBuffIndex] = dataBuff[buffIndex];
    newDataBuffIndex++;

    if (dataBuff[buffIndex] == '\r' || dataBuff[buffIndex] == '\n')
    {
      currentLineChars = 0;
    }
    else
    {
      currentLineChars++;
    }

    buffIndex++;
  }

  newDataBuff[newDataBuffIndex] = 0;
}

void print(char * printString, int line)
{
  bool newline = true;
  int offsetLine = 0;
  int charIndex = 0;
  const int MAX_CHAR = 1000;

  while(printString[charIndex] != 0 && charIndex < MAX_CHAR) {
    if (printString[charIndex] == '\n')
    {
      offsetLine++;
    }

    if (offsetLine == line)
    {
      Screen.clean();
      if (printString[charIndex] == '\n')
      {
        charIndex++;
      }
      Screen.print(printString + charIndex);
      return;
    }

    charIndex++;
  }

  return;
}

int getMaxLine(char * printString) {
  const int MAX_CHAR = 1000;
  int charIndex = 0;
  int line = 0;

  while(printString[charIndex] != 0 && charIndex < MAX_CHAR) {
    if (printString[charIndex] == '\n')
    {
      line++;
    }
    charIndex++;
  }

  return line;
}

void setup() {
  EEPROMInterface eeprom;

  pinMode(USER_BUTTON_A, INPUT);
  pinMode(USER_BUTTON_B, INPUT);

  uint8_t* udsString = (uint8_t*)malloc(DPS_UDS_MAX_LEN + 1);
  uint8_t* udsStringWrap = (uint8_t*)malloc(DPS_UDS_MAX_LEN + 10);
  readEEPROM(Config::uds, udsString);
  wrapIntoLines(udsString, DPS_UDS_MAX_LEN, udsStringWrap, 16);
  
  uint8_t* ssidString = (uint8_t*)malloc(WIFI_SSID_MAX_LEN + 1);
  uint8_t* ssidStringWrap = (uint8_t*)malloc(WIFI_SSID_MAX_LEN + 10);
  readEEPROM(Config::ssid, ssidString);
  wrapIntoLines(ssidString, WIFI_SSID_MAX_LEN, ssidStringWrap, 16);

  uint8_t* pwdString = (uint8_t*)malloc(WIFI_PWD_MAX_LEN + 1);
  uint8_t* pwdStringWrap = (uint8_t*)malloc(WIFI_PWD_MAX_LEN + 10);
  readEEPROM(Config::pwd, pwdString);
  wrapIntoLines(pwdString, WIFI_PWD_MAX_LEN, pwdStringWrap, 16);

  uint8_t* iothubString = (uint8_t*)malloc(AZ_IOT_HUB_MAX_LEN + 1);
  uint8_t* iothubStringWrap = (uint8_t*)malloc(AZ_IOT_HUB_MAX_LEN + 10);
  readEEPROM(Config::iothub, iothubString);
  wrapIntoLines(iothubString, AZ_IOT_HUB_MAX_LEN, iothubStringWrap, 16);

  sprintf(eepromString, "UDS >>>>>>>>>>>>\r\n%s\r\n \r\nWi-Fi SSID >>>>>\r\n%s\r\n\ r\nWi-Fi PWD >>>>>>\r\n%s\r\n \r\nConn Str >>>>>>>\r\n%s", udsStringWrap, ssidStringWrap, pwdStringWrap, iothubStringWrap);
  maxLine = getMaxLine(eepromString);
  print(eepromString, 0);
}

void loop()
{
  if (digitalRead(USER_BUTTON_A) != buttonAStatus)
  {
      if (buttonAStatus == HIGH)
      {
          lineOffset--;
          if (lineOffset < 0)
          {
            lineOffset = maxLine;
          }
          print(eepromString, lineOffset);
      }

      buttonAStatus = digitalRead(USER_BUTTON_A);
  }

  if (digitalRead(USER_BUTTON_B) != buttonBStatus)
  {
      if (buttonBStatus == HIGH)
      {
          lineOffset++;
          if (lineOffset > maxLine)
          {
            lineOffset = 0;
          }
          print(eepromString, lineOffset);
      }

      buttonBStatus = digitalRead(USER_BUTTON_B);
  }

  delay(100);
}
