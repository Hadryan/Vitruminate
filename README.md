# Vitruminate
A decorative audio visualizer

# High Level Description:
My music reactive lamp is one that senses sound from its surrounding, and outputs light in a corresponding level to the volume of the input and its intensity. The brightness and color varies, with cool colors representing low volume, and hot colors representing high volume (volume determines the energy of the song). 

# User Guide:
This item was made with aesthetics in mind. To use it, the system just needs to be turned on, and it will start to take in input from the surroundings. The microphone’s gain has been adjusted so that it is less sensitive to sound, meaning that the music must be adequately loud for the microphone to pick up the noise.

# Components Used:
* ATmega1284
* Arduino Uno
* Addressable LED strip
* Sparkfun Sound Detector
* 5V/15A AC to DC Power Supply (for the LEDs)
* Breadboard, wires, resistor

# Technologies:
* Atmel Studio 7
  * USART to facilitate communication between the ATmega1284 and Arduino Uno
* Arduino IDE
  * FastLED library to control the LED strip
  * SoftwareSerial Library to facilitate communication on the Arduino side (to complete the master/servant setup)

# Demo Video: [UCR EE/CS 120B Winter 2019 - Vitruminate: A Music Reactive Lamp](https://youtu.be/kZhcmGBoQUE)

# Folder Link: [Vitruminate](https://drive.google.com/drive/folders/1TvGw20JAk0O7ApmP-UV12_Tpgq3CmN1b?usp=sharing)

# Source Files (notable):
* [RGB_Led.ino](https://github.com/sitaliaie/Vitruminate/blob/master/RGB_Led/RGB_Led.ino) - Arduino code. Uses the values sent over by the ATmega1284 as its input. Outputs the waveforms/visualizer onto the addressable leds.
* [ReactiveLamp.c](https://github.com/sitaliaie/Vitruminate/blob/master/ReactiveLamp/ReactiveLamp/main.c) (folder name appended, the actual file is main.c) - ATmega1284 code. Drives the state machine as well as taking in the analog signal from the sound detector. Uses a timer to determine when the lamp should turn off
* [Usart.h](https://github.com/sitaliaie/Vitruminate/blob/master/include/usart.h) - This is an include file from the class drive folder. I used the functions defined in this file to facilitate the communication between the Arduino Uno and ATmega1284.
* Not a source file, but I was inspired to make this by the following video: [here](https://www.youtube.com/watch?v=lU1GVVU9gLU)
