# ArduinoGarden
Arduino irrigator with wifi

# Description

# Encountered problems
Over the course of the project I have encountered a few problems there were mostly fixed in the end.

## Broken Arduino
That was the first problem I have encountered. While uploading the code on the Arduino I was getting errors.

'''
stk500_getparm(): (a) protocol error, expect=0x14, resp=0xfc
stk500_recv(): programmer is not responding

vrdude: stk500_getparm(): (a) protocol error, expect=0x14, resp=0xfc
avrdude: stk500_set_extended_parms(): protocol error, expect=0x14, resp=0x94
avrdude: stk500_initialize(): failed
avrdude: initialization failed, rc=-1
avrdude: AVR device initialized and ready to accept instructions
avrdude: Device signature = 0x000000 (retrying)
avrdude: Device signature = 0x000000 (retrying)
avrdude: Device signature = 0x000000
avrdude: Yikes!  Invalid device signature. 
'''

I have tried fixinf the probem by:
- Changing the Board and Processor setting in the Arduino IDE
- Holding the reset button for some amount of time while the program is uploading
- Running the avrdude from CMD
- Changing the USB cable

but nothing fixed the problem. In the end I have just ordered couple of new Arduino Nanos and the everything started working normaly.

## Broken cable
In the middle of working on this project I started getting error while uploading the code on Arduino and ESP8266.
Some of the problmes went away by just wigeling the USB cable but went completly away when I changed the USB cable.

## ESP8266 ESP-01S Wifi module not working properly
This problem was the most time consuming, but in the end the fix was quite simple. The problem turned out to be with the connections of ESP8266 and power limitation of Arduino Nano.
The conenction diagram that worked for me can be found beneeth ([Connection diagram] (#-Programming-ESP8266-ESP-01S-Wifi-module)).
And I have overcome the power limitation by connectiong the ESP8266 to the external power supply (after I have uploaded the code and disconected it from the USB port).

## LED turning on unintentionaly


# Hardware
- Arduino Nano  
- ESP8266 ESP-01S Wifi module

- Power supply (9V 2A)
- 2x LM2596S DC-DC Power Supply
- Relay
- Water pump (5V) + Vinyl tube
- Capacitive Soil Moisture Sensor
- Breadboard + wires
- Resistors (10Kohm, 2Kohm, 1Kohm, 220ohm)
- Button


# Assembely
## Programming ESP8266 ESP-01S Wifi module


## Final assemebly


# Software
