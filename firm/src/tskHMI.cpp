/*
Copyright (c) 2019 Prieto Lucas. All rights reserved.
This file is part of the PLsi project.

PLsi is free software and hardware: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
PLsi is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <globals.h>
#include <plsi.h>
#include <TFT_eSPI.h>
#include <tskHMI.h>
#include <hmi.h>

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

    pressed = tft.getTouch(&ts_x, &ts_y, 350, 10);   
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
    if (hmiPage != hmiPageFirstLoad){
      firstLoad = 1;
      hmiPageFirstLoad = hmiPage;
    }
  
    switch (hmiPage) {
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
      case PAGE_ConfigModbusTCP:
        pageConfigModbusTCP(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigS7:
        pageConfigS7(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
        break;
      case PAGE_ConfigWebServer:
        pageConfigWebServer(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
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
      case PAGE_ConfigIOlocal:
        pageConfigIOlocal(firstLoad, touchType, ts_pressed_x, ts_pressed_y, ts_actual_x, ts_actual_y);
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
     
    if (hmiPage != PAGE_ConfigFirmware){
      configFirmwareEnabled = 0;
    }

    //----------------------------------------------------
    // Firmware was updated -> User message 
    //----------------------------------------------------

    if (settings.general.firmware == FIRMWARE_UPDATED && !configFirmwareEnabled){
      messageCode = MESSAGE_FIRMWARE_UPDATED;
      hmiPageMemory = PAGE_MainMenu;
      hmiPage = PAGE_DialogMessage;
    }



    // Move to HMI TASK for screen capture
    // Issue #11 - For Screen Saver PC connection

    if (I[3]){           
      screenServer();
      delay(1000);   
    }
    delay(5); 
  }
}