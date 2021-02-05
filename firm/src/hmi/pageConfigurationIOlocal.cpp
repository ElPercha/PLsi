#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>
#include <ladder.h>

//--------------------------------------------------------------------------------
// IO Configuration Page
//--------------------------------------------------------------------------------

void pageConfigIOlocal (uint16_t firstLoad, uint16_t touchType, uint16_t ts_x, uint16_t ts_y, uint16_t ts_actual_x, uint16_t ts_actual_y)
{
  //-------------------------------
  // Draw full Page on first load
  //-------------------------------
    
  if(firstLoad){
    drawConfigIOlocal();
  }
    
  //-------------------------------
  // Update required fields
  //-------------------------------

  if (millis() - timerRefreshIOlocal > 500){
    drawConfigIOlocalUpdate ();
    timerRefreshIOlocal = millis();
  }

  //-------------------------------
  // Parse touch screen
  //-------------------------------

  if (touchType == HMI_TOUCHED){
    touchConfigIOlocal(ts_x, ts_y); 
  } 
}

//--------------------------------------------------------------------------------
// IO Configuration draw 
//--------------------------------------------------------------------------------

void drawConfigIOlocal (void){
  tft.fillScreen(COLOR_HMI_CONFIG_IO_BACK_TITLE);
  tft.fillRect(0, HMI_SLOTS_Y, TFT_PIXELS_X, TFT_PIXELS_Y - HMI_SLOTS_Y, COLOR_HMI_CONFIG_IO_BACK);
  tft.drawRect(0, HMI_SLOTS_Y, TFT_PIXELS_X, TFT_PIXELS_Y - HMI_SLOTS_Y, COLOR_HMI_CONFIG_IO_BORDER);

  tft.setTextColor(COLOR_HMI_CONFIG_IO_FONT);
  tft.setTextFont(1);
  tft.setTextSize(1);
  tft.drawCentreString("Local I/O Configuration", TFT_PIXELS_X/2, 15, 4);
  tft.drawCentreString("Touch HERE to go BACK", TFT_PIXELS_X/2, 47, HMI_FONT_SIZE);   

  tft.drawCentreString("SELECT I/O TO EDIT", TFT_PIXELS_X/2, 153, 2);   

  drawConfigIOlocalElements();
  drawConfigIOlocalUpdate();
}

//--------------------------------------------------------------------------------
// IO configuration page
// Touch Screen parsing
//--------------------------------------------------------------------------------

void touchConfigIOlocal(uint16_t ts_x, uint16_t ts_y){
  if(ts_y < HMI_SLOTS_Y){
    hmiPage = PAGE_MainConfig;
  }
  else{
    if(settings.ladder.PLCstate != STOPPED){
      messageCode = MESSAGE_PLC_MUST_BE_IN_STOP1;
      hmiPageMemory = hmiPage;
      hmiPage = PAGE_DialogMessage;
    }
    else{
      uint8_t column  = ts_x / HMI_SLOT_W;
      uint8_t row = (ts_y - HMI_SLOTS_Y) / HMI_SLOT_H;

      if (row == 0){
        if (configInputCanBeAnalog[column] == 1){
          if (settings.io.localInputs[column] != IO_TYPE_DIGITAL){
            settings.io.localInputs[column] = IO_TYPE_DIGITAL;
          }
          else{
            settings.io.localInputs[column] = IO_TYPE_ANALOG_0_10;
          }
          saveSettings();
          configureLocal_IO();
          drawConfigIOlocal();
        }
        else{
          messageCode = MESSAGE_CHANGE_IO_NOT_POSSIBLE;
          hmiPageMemory = hmiPage;
          hmiPage = PAGE_DialogMessage;
        }
      }
      if (row == 3){
        if (column > 0 && column <= IO_LOCAL_OUT_QTY){
          column--;
          if (configOutputCanBeAnalog[column] == 1){
            if (settings.io.localOutputs[column] != IO_TYPE_DIGITAL){
              settings.io.localOutputs[column] = IO_TYPE_DIGITAL;
            }
            else{
              settings.io.localOutputs[column] = IO_TYPE_ANALOG_0_5;
            }
            saveSettings();
            configureLocal_IO();
            drawConfigIOlocal();
          }
          else{
            messageCode = MESSAGE_CHANGE_IO_NOT_POSSIBLE;
            hmiPageMemory = hmiPage;
            hmiPage = PAGE_DialogMessage;
          }
        }
      }
    }
  }
}

//--------------------------------------------------------------------------------
// Draw local IO elements
//--------------------------------------------------------------------------------

void drawConfigIOlocalElements(void){
  tft.drawRect(0, HMI_SLOTS_Y, TFT_PIXELS_X, TFT_PIXELS_Y - HMI_SLOTS_Y, COLOR_HMI_CONFIG_IO_BORDER);

  for (uint8_t c = 0; c < 8; c++){
    // Draw Inputs Status Text + Value  
    if(settings.io.localInputs[c] == IO_TYPE_DIGITAL){
      drawHMIbuttonText(c, 1, 3, "I" + String(c));
    }
    else{
      drawHMIbuttonText(c, 1, 3, "IW" + String(c));
    }  
  }
  // Draw Outputs Status Text + Value  
  for (uint8_t c = 0; c < 6; c++){
    if(settings.io.localOutputs[c] == IO_TYPE_DIGITAL){
      drawHMIbuttonText(c+1, 2, 4, "Q" + String(c));
    }
    else{
      drawHMIbuttonText(c+1, 2, 4, "QW" + String(c));
    }  
  }
}

//--------------------------------------------------------------------------------
// Update local IO animation
//--------------------------------------------------------------------------------

void drawConfigIOlocalUpdate (void){
  for (uint8_t c = 0; c < 8; c++){
    // Draw Inputs Status Text + Value  
    if(settings.io.localInputs[c] == IO_TYPE_DIGITAL){
      drawHMIbutton(c, 0, 0, I[c]);
    }
    else{
      drawHMIAnalogIO_Indicator(c, 0, 0, IW[c]);
    }  
  }
  // Draw Outputs Status Text + Value  
  for (uint8_t c = 0; c < 6; c++){
    if(settings.io.localOutputs[c] == IO_TYPE_DIGITAL){
      drawHMIbutton(c+1, 3, 0, Q[c]);
    }
    else{
      drawHMIAnalogIO_Indicator(c+1, 3, 0, QW[c]);
    }  
  }
}
