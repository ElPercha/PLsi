#include <globals.h>
#include <plsi.h>
#include <disk.h>
 
//----------------------------------------------------
// Override default setting of Serial console speed
//----------------------------------------------------
  
  void serialPortInit(void){
    if (bootSequence == BOOT_SETTINGS_LOADED){
      Serial.begin(settings.general.baudRate); 
      Serial.print("TaskDisk - Serial Port Reconfigured OK. New Speed: ");
      Serial.println(settings.general.baudRate);
      bootSequence = BOOT_TASK_UNLOCKED;
    }
  }
