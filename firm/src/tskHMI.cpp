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
  // Task lock / unlock
  //----------------------------------------------------

  hmiWaitSettings();

  //----------------------------------------------------
  // Task variables
  //----------------------------------------------------

  uint16_t touchType, firstLoad, pressed, ts_x, ts_y, ts_pressed_x = 0, ts_pressed_y = 0, ts_actual_x = 0, ts_actual_y = 0;
  uint16_t pressedAux = 0, releasedAux = 0;
  
  //----------------------------------------------------
  // TFT and TS Display configuration
  //----------------------------------------------------
  
    setDisplay();

    //touch_calibrate(); // Issue #14

  //----------------------------------------------------
  // Task Main loop 
  //----------------------------------------------------

  while(1){
    
    //----------------------------------------------------
    // Touch Screen press type detection
    //----------------------------------------------------

    pressed = tft.getTouch(&ts_x, &ts_y);   
    touchType = HMI_IDLE;

    if (pressed && !pressedAux){
      pressedAux = 1;
      touchType = HMI_TOUCHED;
      ts_pressed_x = ts_x;
      ts_pressed_y = ts_y;
    }
    else if(!pressed && !releasedAux){
      releasedAux = 1;
      touchType = HMI_RELEASED;
    }
    else if(pressed){
      touchType = HMI_TOUCHING;
      ts_actual_x = ts_x;
      ts_actual_y = ts_y;
    }

    if (!pressed){
      pressedAux = 0;
    }
    if (pressed){
      releasedAux = 0;
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
        pageMainMenu(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_MainLadder:
        pageMainLadder(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_LadderEditor:
        pageLadderEditor(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_EditInstructions1:
        pageEditLadderInstructions1(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_EditInstructions2:
        pageEditLadderInstructions2(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_EditInstructions3:
        pageEditLadderInstructions3(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_LadderDetails:
        pageLadderDetails(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_MainConfig:
        pageMainConfig(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigNetwork:
        pageConfigNetwork(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigWiFi:
        pageConfigWiFi(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ScanWiFi:
        pageConfigScanWiFi(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigPLC:
        pageConfigPLC(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigProgram:
        pageConfigProgram(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigIO:
        pageConfigIO(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigHMI:
        pageConfigHMI(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigSystem:
        pageConfigSystem(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigFirmware:
        pageConfigFirmware(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_MainHMI:
        pageMainHMI(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_InputNumber:
        pageInputNumber(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_Keyboard:
        pageKeyboard(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_DialogOkCancel:
        pageDialogOkCancel(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_DialogMessage:
        pageDialogMessage(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;

      default:
        ;
      break;
    }

    //----------------------------------------------------
    // Disable OTA if not in the right page
    //----------------------------------------------------
     
    if (HMI_Page != PAGE_ConfigFirmware){
      configFirmwareEnabled = 0;
    }

    //----------------------------------------------------
    // Firmware was updated -> User message 
    //----------------------------------------------------

    if (settings.general.firmware == FIRMWARE_UPDATED && !configFirmwareEnabled){
      messageCode = MESSAGE_FIRMWARE_UPDATED;
      HMI_PageMemory = PAGE_MainMenu;
      HMI_Page = PAGE_DialogMessage;
    }

    delay(5); 
  }
}