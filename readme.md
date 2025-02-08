## Overview

**Project Title**: BlasterOS

**Project Description**: To create a program in C++ for the Proffieboard v2.2 using an stm32 microcontroller that will play whatever soundfonts and blaster effects your heart desires.

**Project Goals**: To get basic audio reading from an sd, display output to a serial connection

## Instructions for Build and Use

Steps to build and/or run the software:

1. Connect proffieboard v2.2
2. upload program using arduino IDE
3. connect buttons to proffieboard for digital input pins
4. watch the serial console

Instructions for using the software:

1. if wired buttons exist, press and watch the pew in the serial, use a switch for the stun mode.
2. Make sure the files for your soundfont are on your proffie SD card.
3. font change with the font button.

## Development Environment 

To recreate the development environment, you need the following software and/or libraries with the specified versions:

* Arduino IDE
* Proffieboard V2 set as the board
* everything else should just fall into place.

## Useful Websites to Learn More

I found these websites useful in developing this software:

* [Arduino](https://www.arduino.cc/en/Tutorial/LibraryExamples/ReadWrite) (documentation on sd interfacing)
* [chat.openai](chat.openai.com) (useful in debugging)
* [proffieboard documentation and KiCAD files](https://fredrik.hubbe.net/lightsaber/v5/board22.html) (very helpful in understanding the CPU)

## Future Work

The following items I plan to fix, improve, and/or add to this project in the future:

* [ ] LED writing with neopixel strips
* [ ] complete hardware to test
