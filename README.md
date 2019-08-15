The purpose of this project is to allow me to create custom LED fixtures and not have to rewrite patterns to display correctly, no matter the arrangement of LEDs.

My first step has been to figure out how to make the program and data structures flexible and robust enough for a lot of different use cases. My next step is to refactor all the functionality into a few classes, which is the project I'm working on now.

Start in 8_Strip_Controller.ino. Excecution starts at the top of the file, runs the setup() function once, and then repeats the loop() function forever.

- The Universe is responsible for managing all information regarding the physical LEDs and updating everything when an input is received.

- universeSettings.h contains all the information about the fixture the software is currently running on.

- The LEDStrips are responsible for managing the parameters associated with a currently running pattern like speed, hue, etc.

- patterns.h and patterns.cpp contain the logic to calculate patterns based on a given input of the PatternVars struct.

- web.h contains functions for user input using a self hosted web page.

- webInput.h contains functions for user input using an Android or iOS app.

- physicalInputs.h contains all functions relating to the use of physical buttons, potentiometers, etc.

- debug.h contains the debug macro D(x) as well as functions to help with debugging.

- The Oscillator class will be a more functional version of FastLED's built in beatsin() function, but hasn't been implemented yet.

- palettes.h and gradientPalettes.h contain collections of predefined palettes.

- tasks.h and tasks.cpp contain the code for using the second core of the ESP32 to output the CRGBArray to the physical LEDs.
