# DelayBasedFX

Work In Progress 

This is a working template for a multi delay-based FX plugin based on the ‘The Audio Programmer’ circular buffer tutorials and Daniel Walz’s ‘ffTapeDelay’ code (links below):

https://www.youtube.com/watch?v=IRFUYGkMV8w

https://github.com/ffAudio/ffTapeDelay

The main idea behind this plugin is to keep on building on the existing simple delay by adding other delay-based FX and creating a modular, multi fx processor and it is mainly a personal exercise to learn how to create different audio FX using the Juce framework:

https://juce.com

In its current state, the plugin tries to read the data of the circular buffer inverted for a given amount of time. Inevitably, this will lead to clicks and artifacts so I am in the process of trying to work out how to deal with this.

