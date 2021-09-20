This project lets users push down "valves" pushbuttons in realistic combinations and adjust the position of a potentiometer to "play" a digital trumpet.

This project requires the following:
* Arduino Uno and cables/wires
* 4 x pushbuttons
* 1 potentiometer
* 1 piezo buzzer

## Building
The four buttons (three valves and one play-select button that controls whether the buzzer produces sound) must be connected to the pins on the Arduino as defined in the program. This configuration uses the "INPUT_PULLUP" feature of the Arduino's pins so each button is only connected to ground and the specified pin.

The outer two pins on the potentiometer shoud be connected to 5V and GND (either way works, but it will reverse which direction corresponds to low and high notes on the potentiometer) and the middle pin should be connected to the proper pin as defined in the program (this needs to be an analog-input pin).

The piezo buzzer has two connections- the side marked with the (+) should be connected to the pin specified in the program (must be a PWM pin) and the other pin should be connected to ground.

## Playing
To "play" the digital trumpet, push down on the buttons as if they were valves on an actual trumpet (see trumpet fingering charts online; to ensure enough separation between notes with the same valve combinations, the lower octave fingerings are used for both octaves).

In order to make sound, the fourth "play-select" button must also be depressed. Because multiple notes use the same valve combinations, you must twist the potentiometer to indicate whether you want to play higher or lower notes (arguably the trickiest part- this is analogous to a trumpet player adjusting their amisher and airflow into the instrumet). 

*Happy playing!*

## Example:
See the example image below, and a [demo video hosted on imgur](https://imgur.com/a/sAthne2)!

![example](example.png)