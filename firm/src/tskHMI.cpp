#include <globals.h>
#include <plsi.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <tskHMI.h>

//--------------------------------------------------------------------------------
// HMI Task 
// Display (tft) and Touch Screen (ts) management
// Running on Core 0
//--------------------------------------------------------------------------------

void TaskHMI(void *pvParameters)
{
  (void) pvParameters;
    
  //----------------------------------------------------
  // Task global variables
  //----------------------------------------------------

  uint16_t ts_x, ts_y, touchType, pressed, firstLoad;
  uint16_t calData[5] = {TS_LEFT_X, TS_RIGHT_X, TS_TOP_Y, TS_BOTTOM_Y, TS_ROTATION};

  //----------------------------------------------------
  // TFT and TS Display configuration
  //----------------------------------------------------
  
  tft.init();
  tft.setRotation(TFT_ROTATION);
  
  tft.setTouch(calData);
  //touch_calibrate();

  //----------------------------------------------------
  // HMI Touch Screen Global Variables init
  //----------------------------------------------------

  HMI_Touched.Menu = 0;
  HMI_Touched.Logic.Value = 0;
  HMI_Touched.Logic.Row = 0;
  HMI_Touched.Logic.Col = 0;

  //----------------------------------------------------
  // Task Main loop 
  //----------------------------------------------------

  while(1){
    
    //----------------------------------------------------
    // Touch Screen press type detection
    //----------------------------------------------------

    pressed = tft.getTouch(&ts_x, &ts_y);
    touchType = 0;

    if (pressed && !pressedAux){
      pressedAux = 1;
      touchType = ONECLICK;
    }
    if (!pressed){
      pressedAux = 0;
    }

    //----------------------------------------------------
    // Page selection management
    //----------------------------------------------------
    
    firstLoad = 0; 
    if (HMI_Page != HMI_PagePrevious){
      firstLoad = 1;
      HMI_PagePrevious = HMI_Page;
    }

    switch (HMI_Page) {
      case PAGE_MainMenu: 
        pageMainMenu(firstLoad, touchType, ts_x, ts_y);
        break;
      case PAGE_MainLadder:
        pageMainLadder(firstLoad, touchType, ts_x, ts_y);
        break;
      case PAGE_MainHMI:
        pageMainHMI(firstLoad, touchType, ts_x, ts_y);
        break;
      case PAGE_MainConfig:
        pageMainConfig(firstLoad, touchType, ts_x, ts_y);
        break;
      case PAGE_InputNumber:
        pageInputNumber(firstLoad, touchType, ts_x, ts_y);
        break;
      default:
        ;
      break;
    }
    delay(5); 
  }
}