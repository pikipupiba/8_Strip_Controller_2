Initially based largely on the ESP32 FastLED webserver example by Jason Coon, this has grown into an effective monstrosity that can display different patters to different strips and is controlled via UDP instead of a self hosted web server.

The purpose of this project is to allow me to create custom LED fixtures and not have to rewrite patterns to display correctly, no matter the arrangement of LEDs.

My first step has been to figure out how to make the program and data structures flexible and robust enough for a lot of different use cases.
