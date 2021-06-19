
/*
    Modbus Library for Arduino
    
    Copyright (C) 2019-2020 Alexander Emelianov (a.m.emelianov@gmail.com)
	https://github.com/emelianov/modbus-esp8266
	This code is licensed under the BSD New License. See LICENSE.txt for more info.
    
Prefixes:
MODBUS_     Global library settings
MODBUSIP_   Settings for TCP and TLS both
MODBUSTCP_  Settings for TCP
MODBUSTLS_  Settings for TLS
MODBUSRTU_  Settings for RTU
MODBUSAPI_  Settings for API
*/
#pragma once

/*
#define MODBUS_GLOBAL_REGS
If defined Modbus registers will be shared across all Modbus* instances.
If not defined each Modbus object will have own registers set.
*/
#define MODBUS_GLOBAL_REGS

/*
#define MODBUS_USE_STL
If defined C STL will be used.
*/
#if defined(ESP8266) || defined(ESP32) || defined(ARDUINO_ARCH_STM32)
#define MODBUS_USE_STL
#endif

/*
#define MODBUS_MAX_REGS     32
If defined regisers count will be limited.
*/ 
//#define MODBUS_MAX_REGS     32

#define MODBUS_ADD_REG
#define MODBUS_MAX_FRAME   256
//#define MODBUS_STATIC_FRAME
#define MODBUS_MAX_WORDS 0x007D
#define MODBUS_MAX_BITS 0x07D0
#define MODBUS_FILES
#define MODBUSTCP_PORT 	  502
#define MODBUSTLS_PORT 	  802
#define MODBUSIP_MAXFRAME 200
#define MODBUSIP_TIMEOUT 1000
#define MODBUSIP_UNIT	  255
#define MODBUSIP_MAX_TRANSACTIONS 16
#define MODBUSIP_MAX_CLIENTS	  4
#define MODBUSIP_UNIQUE_CLIENTS
#define MODBUSIP_MAX_READMS 100
#define MODBUSIP_FULL

//#define MODBUSRTU_DEBUG
#define MODBUSRTU_BROADCAST 0
#define MB_RESERVE 248
#define MB_SERIAL_BUFFER 128
#define MB_MAX_TIME 10
#define MODBUSRTU_TIMEOUT 1000
#define MODBUSRTU_MAX_READMS 100

#define MODBUSAPI_LEGACY
#define MODBUSAPI_OPTIONAL