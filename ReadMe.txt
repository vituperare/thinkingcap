The Thinking Cap v1.0 is the first major release of Grindhouse Wet Wares' implementation of the 
tDCS (transcranial Direct Current Stimulation and CES (Cranial Electrotherapy Stimulation)
concepts.  The idea is to stimulate your brain with direct current (in the case of tDCS)
or with square waves of current (in the case of CES) which can either raise or lower the
potential energy of the stimulated neurons, depending on the orientation of electrodes.
This allows them to fire more or less easily, and activates or deactivates a given region,
thus engaging certain brain states.

The code (included) is programmed to control an Arduino-compatible microcontroller to deliver
the necessary current.  It comes in the form of a library, so the hacker can choose his way of
controlling the current.  To create an instantiation of the ThinkingCap class, simply call the
"ThinkingCap" constructor, and then call the methods corresponding to the desired action.

The tDCS setting uses a current source and PWM to ramp up the current at the beginning, and ramp
it back down after a given stimulation time (20 minutes by default, but this setting is also
changeable).  The CES setting pulls a constant square wave, with a frequency to be set by the
user.

If the component values from the schematic are used, the current pulled should be roughly 0.5 mA
or less, but by changing these values, the current level can be manipulated.  However, pulling
currents in excess of 2 mA is not recommended for any use.

The "software" folder contains the software necessary to control the Thinking Cap.  This consists
in an Arduino library called "thinkingcap" and a sample Arduino sketch called "TCexample.ino" that
imports this library.  The example code is designed to apply CES or tDCS depending on the position
of a switch, and to begin when a push-button is activated.

THe "hardware" folder contains gerber files, a bill of materials, and Eagle files necessary to create
a PCB for the Thinking Cap.  This is included within the "thinkingcap10a" folder; the "thinkingcap10b"
folder contains a design for a separate circuit that is not released nor recommended for use.

Thinking Cap v1.0 designed by ianmathwiz7; released 7-1-2013 by Grindhouse Wetware.