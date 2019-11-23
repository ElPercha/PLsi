#ifndef MAIN_H
#define MAIN_H 

//--------------------------------------------------------------------------------
// RTOS tasks definition  
//--------------------------------------------------------------------------------
void TaskHMI    ( void *pvParameters ); // Core 0
void TaskDisk   ( void *pvParameters ); // Core 0
void TaskLadder ( void *pvParameters ); // Core 1

//--------------------------------------------------------------------------------
// Wi Fi initial setup  
//--------------------------------------------------------------------------------
//const char* ssid = "2203Alden";
//const char* password = "HolaHola";
//WebServer server(80);

#endif
