// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Touch screen and TFT display initializations
//--------------------------------------------------------------------------------

void setDisplay(void) {
  tft.init();
  tft.setRotation(TFT_ROTATION);  

  uint16_t calData[5];
  calData[0] = settings.hmi.ts.leftX;
  calData[1] = settings.hmi.ts.rightX;
  calData[2] = settings.hmi.ts.topY;
  calData[3] = settings.hmi.ts.bottomY;
  calData[4] = TS_ROTATION;

  tft.setTouch(calData); 
}

//--------------------------------------------------------------------------------
// Touch screen calibration routine
//--------------------------------------------------------------------------------

void touch_calibrate(){
  uint16_t calData[5];

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println("Touch corners as indicated");

  tft.setTextFont(1);
  tft.println();

  tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

  Serial.println("Calibration complete!");
  Serial.print("Calibration Value 0: ");
  Serial.println(calData[0]);
  Serial.print("Calibration Value 1: ");
  Serial.println(calData[1]);
  Serial.print("Calibration Value 2: ");
  Serial.println(calData[2]);
  Serial.print("Calibration Value 3: ");
  Serial.println(calData[3]);
  Serial.print("Calibration Value 4: ");
  Serial.println(calData[4]);

  tft.setTouch(calData);

  settings.hmi.ts.leftX   = calData[0];
  settings.hmi.ts.rightX  = calData[1];
  settings.hmi.ts.topY    = calData[2];
  settings.hmi.ts.bottomY = calData[3];
  saveSettings();
}
