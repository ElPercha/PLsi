#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Touch screen calibration routine
//--------------------------------------------------------------------------------

void touch_calibrate()
{
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

  tft.setTouch(calData); // LucasSettings

}
