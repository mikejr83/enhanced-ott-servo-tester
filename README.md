# Enhanced Over-the-Top Servo Tester

Enhanced version of OTT Servo Tester by MajicDesigns OTT Servo Tester: https://github.com/MajicDesigns/OTTServoTester

My version of the project using a Raspberry Pi Pico, an OLED display, and a different interface to accomplish the same end goal.

# Goals

The first and foremost goal is to recreate the Magic Designs OTT Servo Tester with an OLED display. The two line LCD on the original was meh. OLEDs are so much cooler!

I also want to be able to do the following:

- [ ] Read SBUS in and show the values for vaious channels
- [ ] Multiple RX PWM inputs and show the values that the RX is receiving on those channels
- [ ] Pass through from inputs to servos for both SBUS and PWM
- [ ] ESC throttle channel and AMRT comparion*
- [ ] Powered by the RC system or external battery.
- [ ] Show the current voltage of the RC system.

\* I am a F5J sailplane pilot. We use an altitude measuring and recording device that sits between the receiver and ESC. It turns the motor off after 30secs. There are often issues where the pulse rate from the receiver will cause the AMRT to reset. This ends up in no altitude being recorded and thus a zero score for the round.

# BOM

* Microcontroller: Raspberry Pi Pico
* OLED Display: Currently using the [WaveShare 1.5in RGB OLED Module](https://www.waveshare.com/wiki/1.5inch_RGB_OLED_Module)
* HW-221 Level Shifter / TXB0108 - Insuring the voltage that is driving the servos and servo signals are safe for the microcontroller (F5J models typically drive servos between 7.8 and 8.2v)

## Possible Inclusions

I'd like to convert the WaveShare 1.3in OLED HAT for use in this project. It includes a 5 way joystick (up/down, left/right, press) and three buttons. The current issue is figuring out the pinout on the 40pin Raspberry Pi HAT connector to connect to the Pico.

## Hardware Notes

The goal is to have a small box that can be powered from the RC system it is monitoring or from a small battery when doing servo testing. As development progresses I'll be uploading schematics on how this will work. I'm sure this will be interesting.

# Adafruit GFX and SSD1351 Library

This branch represents getting the [WaveShare 1.5in OLED RGB display](https://www.waveshare.com/wiki/1.5inch_RGB_OLED_Module) to work with the Adafruit GFX and SSD135 libraries.

# Credits

Thanks to MajicDesigns for the documentation on their project. Having the code available to look over is helping me develop my solution.

Rainbow Dash Splash Screen Image: [AtomicGreymon @ DeviantArt](https://www.deviantart.com/atomicgreymon/art/Rainbow-Dash-Salute-200994549)