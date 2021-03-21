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
#include <ladder.h>

//--------------------------------------------------------------------------------
// Local Inputs
//--------------------------------------------------------------------------------

void readInputsLocal(void){
  I[0] = !digitalRead(INPUT_00); 
  I[1] = !digitalRead(INPUT_01); 
  I[2] = !digitalRead(INPUT_02); 
  I[3] = !digitalRead(INPUT_03); 
  I[4] = !digitalRead(INPUT_04); 
  I[5] = !digitalRead(INPUT_05); 

  if (settings.io.localInputs[6] == IO_TYPE_DIGITAL){
    I[6] = !digitalRead(INPUT_06); 
  }
  else{
    uint16_t auxAnalogIn= uint16_t(double(analogRead(AN_INPUT_00)) * ANALOG_RESOLUTION/ANALOG_IN_CALIBRATION);

    if (auxAnalogIn != 0){
      auxAnalogIn = auxAnalogIn + ANALOG_IN_ZERO_OFFSET;
    }

    if (auxAnalogIn >= ANALOG_RESOLUTION){
      IW[6] = ANALOG_RESOLUTION - 1;
    }
    else{
      IW[6] = analogInfilter(0, auxAnalogIn);
    }
  }

  if (settings.io.localInputs[7] == IO_TYPE_DIGITAL){
    I[7] = !digitalRead(INPUT_07); 
  }
  else{
    uint16_t auxAnalogIn= uint16_t(double(analogRead(AN_INPUT_01)) * ANALOG_RESOLUTION/ANALOG_IN_CALIBRATION);

    if (auxAnalogIn != 0){
      auxAnalogIn = auxAnalogIn + ANALOG_IN_ZERO_OFFSET;
    }

    if (auxAnalogIn >= ANALOG_RESOLUTION){
      IW[7] = ANALOG_RESOLUTION - 1;
    }
    else{
      IW[7] = analogInfilter(1, auxAnalogIn);
    }
  }
}

//--------------------------------------------------------------------------------
// Local Outputs
// ESP32 dac resolution is 0-255 PLsi standard analog I/O resolution is 0-1024
//--------------------------------------------------------------------------------

void writeOutputsLocal(void){
  digitalWrite(OUTPUT_00, Q[0]);
  digitalWrite(OUTPUT_01, Q[1]);
  digitalWrite(OUTPUT_02, Q[2]);
  digitalWrite(OUTPUT_03, Q[3]);
  
  if (settings.io.localOutputs[4] == IO_TYPE_DIGITAL){
    digitalWrite(OUTPUT_04, Q[4]);
  }
  else{
    dacWrite(AN_OUTPUT_00, QW[4] * ANALOG_OUT_CALIBRATION/ANALOG_RESOLUTION /(ANALOG_RESOLUTION/ANALOG_OUT_RESOLUTION));
  }

  if (settings.io.localOutputs[5] == IO_TYPE_DIGITAL){
    digitalWrite(OUTPUT_05, Q[5]);
  }
  else{
    dacWrite(AN_OUTPUT_01, QW[5] * ANALOG_OUT_CALIBRATION/ANALOG_RESOLUTION /(ANALOG_RESOLUTION/ANALOG_OUT_RESOLUTION));
  }
}

//--------------------------------------------------------------------------------
// IO physical assignment 
// 
// Attenuation values:
//    0db   for a full-scale voltage of 1.1V
//    2.5db for a full-scale voltage of 1.5V
//    6db   for a full-scale voltage of 2.2V
//    11db  for a full-scale voltage of 3.9V
//--------------------------------------------------------------------------------

void configureLocal_IO(void){
  analogSetAttenuation(ADC_6db);
  analogSetWidth(ANALOG_IN_BITS);
  analogSetClockDiv(ANALOG_CLOCK_DIVIDER);

  pinMode(INPUT_00, INPUT);
  pinMode(INPUT_01, INPUT);
  pinMode(INPUT_02, INPUT);
  pinMode(INPUT_03, INPUT);
  pinMode(INPUT_04, INPUT);
  pinMode(INPUT_05, INPUT);
  pinMode(INPUT_06, INPUT);
  pinMode(INPUT_07, INPUT);
  
  pinMode(OUTPUT_00, OUTPUT);
  pinMode(OUTPUT_01, OUTPUT);
  pinMode(OUTPUT_02, OUTPUT);
  pinMode(OUTPUT_03, OUTPUT);
  
  if (settings.io.localOutputs[4] == IO_TYPE_DIGITAL){
    pinMode(OUTPUT_04, OUTPUT);
  }
  else{
    pinMode(AN_OUTPUT_00, ANALOG);
  }

  if (settings.io.localOutputs[5] == IO_TYPE_DIGITAL){
    pinMode(OUTPUT_05, OUTPUT);
  }
  else{
    pinMode(AN_OUTPUT_01, ANALOG);
  }
}

//--------------------------------------------------------------------------------
// Analog inputs moving average filter
//--------------------------------------------------------------------------------

uint16_t analogInfilter(uint16_t index, uint16_t value){
  analogInFilter[index][analogInFilterPointer[index]] = value;
  analogInFilterPointer[index]++;

  if (analogInFilterPointer[index] >= ANALOG_FILTER_SAMPLES){
    analogInFilterPointer[index] = 0;
  }

  double average = 0;
  for (uint16_t i= 0; i < ANALOG_FILTER_SAMPLES; i++){
    average += analogInFilter[index][i];
  }
  return uint16_t(average/ANALOG_FILTER_SAMPLES);
}

