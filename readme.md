# **PLsi General Info**

+ Project Name: PLsi  
+ Date: November 1, 2019  
+ email: funnyautomation@gmail.com  
+ Description: Fully functional PLC based on ESP32 module and 320x240 SPI Touchscreen Display  
+ Estimated total cost: Less than 20 USD

-----------------------------------------------------------------------------------------

# Hardware Version 0

- ESP32 Processor
	+ Dual Core. 
	+ Ladder Logic runs in a separated Core.
	+ Wi-Fi connectivity
- 2.8" Display with Touch interface for:
	+ PLC Programming and debugging
	+ HMI Control
	+ Configuration
- 8 Hardware Inputs 5-24VDC Isolated
- 6 Hardware Relay Outputs 
- Removable Terminal blocks
- I2C port for hardwired expansions
- USB 5Vdc main power supply
- SD Card slot (currently doesn't have implemented functionalities)

-----------------------------------------------------------------------------------------

# Firmware Version 0.00.00

- **Date: 10:42 AM 12/24/2020**
- **Filename: "PLsi v0.00.00.bin"**
- **Comment: First stable version**
 
Software Main functionalities:

- PLC Instruction set: 29 instructions
	+ Boolean instructions full set
	+ Timers and Counters full set
	+ 16 bit math functions
- PLC Memory Areas:
	+ 2000 Marks (M)
	+ 200 Counters (C) 
	+ 300 Timers (T)
	+ 10000 Registers 16bits (D)
- Row, Column and Network Editor
- Network Navigation
- Online Edition (with PLC running)
- RUN/STOP with user confirmation
- PLC Program space: 400 networks of 6x5 cells (12K boolean instructions)
- Up to 4 PLC programs stored on internal memory (max. 400 networks each)
- Fast Scan time of 2.5ms for 1000 instructions
- HMI "Fix" version implemented (User cannot edit memory areas nor texts)
- WiFi configuration with SSID scanning functionality.
- Firmware update via Web Page

Bug fixes:

- None (It's the first version :)

-----------------------------------------------------------------------------------------






