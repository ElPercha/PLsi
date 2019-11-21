#ifndef MAIN_H
#define MAIN_H 

//--------------------------------------------------------------------------------
// RTOS tasks definition  
//--------------------------------------------------------------------------------
void TaskHMI   ( void *pvParameters );
void TaskLadder( void *pvParameters );
void TaskWeb   ( void *pvParameters );

//--------------------------------------------------------------------------------
// Wi Fi initial setup  
//--------------------------------------------------------------------------------
//const char* ssid = "2203Alden";
//const char* password = "HolaHola";
//WebServer server(80);

#endif
