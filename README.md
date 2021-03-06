# ArduinoGarden
Arduino irrigator with wifi

# Description
After quite some years (6 years maybe?) of not touching the Arduino, I have decided to do a simple project.  
The goal of the project was to create a simple irrigation system for my chilly plant and connect it to the internet so I would be able to monitor the moisture data.

# Encountered problems
Throughout the project I have encountered a few problems there were mostly fixed in the end.

## Broken Arduino
That was the first problem I have encountered. While uploading the code on the Arduino I was getting errors.

```
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
```

I have tried fixing the problem by:
- Changing the Board and Processor setting in the Arduino IDE
- Holding the reset button for some amount of time while the program is uploading
- Running the avrdude from CMD
- Changing the USB cable

but nothing fixed the problem. In the end, I have just ordered a couple of new Arduino Nanos and everything started working normally.

## Broken cable
In the middle of working on this project, I started getting an error while uploading the code on Arduino and ESP8266.  
Some of the problems went away by just wiggling the USB cable but went completely away when I changed the USB cable.

## ESP8266 ESP-01S Wifi module not working properly
This problem was the most time consuming, but in the end, the fix was quite simple. The problem turned out to be with the connections of ESP8266 and the power limitation of Arduino Nano.  
The connection diagram that worked for me can be found beneath ([Connection diagram] (#-Programming-ESP8266-ESP-01S-Wifi-module)).  
And I have overcome the power limitation by connecting the ESP8266 to the external power supply (after I have uploaded the code and disconnected it from the USB port).

## LED turning on unintentionally
This was the only problem I still haven't fixed. The problem is that when the pump is running the LED light starts to shine very dimly. This is probably caused by long wires and shortening would fix this, but I still haven't tried that.

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
For now, the connection diagrams are only in text form but I will try to update them with pictures.

## ESP8266 ESP-01S Wifi module - Programing diagram
```
 ESP-01S | ARDUINO
---------|--------
     VCC | 3.3V
     GND | GND
      TX | TX
      RX | (voltage divider) 1Kohm -> RX (connects here) -> 2Kohm -> GND
   CH_EN |  10Kohm -> GND
     RST | floating
GPIO - 0 | GND
GPIO - 2 | floating
```

## ESP8266 ESP-01S Wifi module - Testing diagram
```
 ESP-01S | LM2596S DC-DC (3.3V output)
---------|--------
     VCC | 3.3V
     GND | GND
      TX | floating or RX
      RX | floating or TX
   CH_EN | floating
     RST | floating
GPIO - 0 | floating
GPIO - 2 | floating
```

## Final assembly diagram


# Software
## Arduino
## ESP8266
## API
