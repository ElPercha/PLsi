// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#include <globals.h>
#include <TFT_eSPI.h>
#include <hmi.h>

//--------------------------------------------------------------------------------
// Return the max Memory valid index for the given Type of Memory area
//--------------------------------------------------------------------------------

uint16_t getMaxMemoryAddress(uint16_t type){
  if(type == TypeM)  {return QTY_M - 1;}
  if(type == TypeQ)  {return QTY_Q - 1;}
  if(type == TypeI)  {return QTY_I - 1;}
  if(type == TypeCd) {return QTY_C - 1;}
  if(type == TypeCr) {return QTY_C - 1;}
  if(type == TypeTd) {return QTY_T - 1;}
  if(type == TypeTr) {return QTY_T - 1;}
  if(type == TypeIW) {return QTY_IW - 1;}
  if(type == TypeQW) {return QTY_QW - 1;}
  if(type == TypeC)  {return QTY_C - 1;}
  if(type == TypeT)  {return QTY_T - 1;}
  if(type == TypeD)  {return QTY_D - 1;}
  if(type == TypeK)  {return 32768;}
  if(type == TypeR)  {return QTY_R - 1;}
  if(type == TypeKR) {return 0;}
  return 0;
}

//--------------------------------------------------------------------------------
// Return the max Memory valid index for the given Type of Memory area
//--------------------------------------------------------------------------------

int16_t getMinMemoryAddress(uint16_t type){
  if(type == TypeK)  {return -32767;}
  return 0;
}

//--------------------------------------------------------------------------------
// Change Timer Base Time
//      1 - ms
//     10 - 0.01 sec
//    100	- 0.1 sec
//   1000	- sec
//  60000	- min
//--------------------------------------------------------------------------------

void changeTimerBaseTime(void){
  uint16_t indexTimer = 10;
  for (uint16_t i = 0; i < 5; i++){
    if (editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type == timerBaseTime[i]){
      indexTimer = i;
    }
  }
  if (indexTimer == 10){
    editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type = timerBaseTime[3]; // Default to Seconds
    indexTimer = 3;
  }
  else {
    indexTimer++;
    if (indexTimer >= 5){
      indexTimer = 0;
    }
    editingNetwork.Cells[ladderEditorRow+1][ladderEditorColumn].Type = timerBaseTime[indexTimer]; 
  }
}

//--------------------------------------------------------------------------------
// Limit the Memory Range per Type of memory Area
// If Index is invalid, set to max possible Index
//--------------------------------------------------------------------------------

void limitMemoryRange(void){
  if (editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data > getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type)){
    editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Data = getMaxMemoryAddress(editingNetwork.Cells[ladderEditorRow][ladderEditorColumn].Type);
  }
}

