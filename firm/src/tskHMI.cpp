#include <globals.h>
#include <plsi.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <tskHMI.h> // Lucas there is a issue with this calls, should be first this one but creates other issues

//--------------------------------------------------------------------------------
// HMI Task 
// Display (tft) and Touch Screen (ts) management
// Running on Core 0
//--------------------------------------------------------------------------------

void TaskHMI(void *pvParameters)
{
  (void) pvParameters;

  //----------------------------------------------------
  // Task lock / unlock
  //----------------------------------------------------

  hmiWaitSettings();

  //----------------------------------------------------
  // Task variables
  //----------------------------------------------------

  uint16_t ts_x, ts_y, touchType, firstLoad, pressed, pressedAux = 0;

  //----------------------------------------------------
  // TFT and TS Display configuration
  //----------------------------------------------------
  
    setDisplay();

    //touch_calibrate();

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
      case PAGE_LadderEditor:
        pageLadderEditor(firstLoad, touchType, ts_x, ts_y);
        break;
      case PAGE_LadderDetails:
        pageLadderDetails(firstLoad, touchType, ts_x, ts_y);
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