## ATtiny85 Continuity Tester

This is a personal project that I've been working on and off for the last 4 months or so. My intention is to create a compact continuity tester using the ATtiny85 microcontroller. It is inspired by this article: (http://www.technoblogy.com/show?1YON)

## Personal Goals

As someone who enjoys making PCB's, I wanted to challenge myself by having a couple of design challenges to work around:

Needs:
-Needs create a PCB that will fit inside an expo marker
-Needs to have an additional functionality that was not present in the original inspiration source

Wants:
-Possible future revisions with an onboard USB-C charging capability an Li-Ion rechargeable battery.


So far, I've also toyed with the idea of adding a potentiometer in place of the voltage divider in order to allow for adjustment to the continuity detection threshold.

#How it works

The ATtiny85 contains an onboard analog comparator. This allows me to set an adjustable input (V+) to a very small (5mV) voltage. The other input (V-) then becomes our probe. When not touching a circuit, the probe input sits at 5V. When continuity is detected using the probe input, the voltage drops below 5mV, our V+ voltage, and triggers the comparator output to turn on. When the comparator output turns on, we then hear our buzzer ringing and our LED lighting up. 

## Hardware

-ATtiny85 Microcontroller
-Piezo Buzzer
-LED
-Potentiometer(?)
