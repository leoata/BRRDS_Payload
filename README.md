# BRRDS_PayloadE (PlatformIO)

## Install Dependencies

### Step 1
Install PlatformIO.

This program allows us to interface with the Arduino and helps us do basic things like uploading our code and monitoring the output much easier.

Full instructions from here (OSX, Linux, Win): https://docs.platformio.org/en/latest//core/installation.html#installation-methods
Run commands in the Terminal app (Mac/Linux).
*Note*: Do NOT download the PlatformIO VSCode package if you want to follow these instructions. We are using CLion not VSCode so we want the CLI.

For your convenience, I condensed the instructions here:

#### All Platforms
Download https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py

Run with python: `python3 get-platformio.py` OR `python get-platformio.py`

#### Linux-specific

Run in a user shell `python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"`

If you get the error `bash: command not found: python3`, run `python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"`

#### Mac-specific
If you don't already have homebrew, install by running this in a terminal window
`/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`

Then, run `brew install platformio`

### Step 2 (Optional)

Install CLion.

This is the IDE that I (Leo) use because it has the best autocompletion out of any IDE.

Download from here (OSX, Linux, Win): https://www.jetbrains.com/clion/

Use the Community Edition. If you want, you can obtain an education license and download the Ultimate version, although it isn't necessary.

### Step 3 (Optional)
Install the CLion PlatformIO Plugin.

* Open CLion
* Go to https://plugins.jetbrains.com/plugin/13922-platformio-for-clion
* Click "Install to CLion 20XX.X.X"
* Bring the CLion IDE to the foreground (click on it so it comes up on your screen)
* Click OK

## Basic Commands for Development

### Install a library
First, find the ID of the library that you want to install. For this example, I will be installing "Adafruit MPRLS Library"

Make sure platformio is in your PATH environment variable before running the following commands (don't include the $ when running on your computer)
```shell
$ platformio lib search MPRLS

Found 1 libraries:

Adafruit MPRLS Library
======================
#ID: 5787
Arduino library for MPRLS series pressure sensors

Keywords: sensors
Compatible frameworks: Arduino
Compatible platforms: Infineon XMC, Kendryte K210, GigaDevice GD32V, ASR Microelectronics ASR650x, Atmel AVR, Atmel SAM, Espressif 8266, Intel ARC32, Microchip PIC32, Nordic nRF51, ST STM32, Teensy, TI MSP430, TI TIVA, Espressif 32, Nordic nRF52, ST STM8, Atmel megaAVR, Logic Green boards, HWLogic, LOGICROM Development Platform, Raspberry Pi RP2040
Authors: Adafruit
```
Look! We found the Adafruit MPRLS Library with an ID of 5787. Now, we can install it (again, don't include the $ in your command)
```shell
$ platformio lib install 5787

Library Storage: /BRRDS_PayloadA/.pio/libdeps/nanoatmega328
Library Manager: Installing id:5787
Downloading  [####################################]  100%
Unpacking  [####################################]  100%
Library Manager: Adafruit MPRLS Library @ 1.2.0 has been installed!
Library Manager: Installing dependencies...
Library Manager: Adafruit Unified Sensor @ 1.1.4 is already installed
Library Manager: Adafruit BusIO @ 1.9.3 is already installed

```
Depending on which library you install, you might have more or less dependencies installed.

### Uploading the code to the board
To upload the code with platformio:

* Open a shell or command line
* Navigate to the project directory
* Run the following:
```shell
$ pio run --target clean && pio run --target upload
```
### Monitor the Serial
* Open a shell or command line
* Replace BAUD_RATE with your desired baud rate
* Run the following:
 ```shell
$ pio device monitor -bBAUD_RATE
```