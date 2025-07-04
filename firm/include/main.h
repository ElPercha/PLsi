// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#ifndef MAIN_H
#define MAIN_H 

//--------------------------------------------------------------------------------
// RTOS tasks definition  
//--------------------------------------------------------------------------------

void TaskHMI    ( void *pvParameters ); // Core 0
void TaskDisk   ( void *pvParameters ); // Core 0
void TaskWiFi   ( void *pvParameters ); // Core 0
void TaskLadder ( void *pvParameters ); // Core 1

#endif