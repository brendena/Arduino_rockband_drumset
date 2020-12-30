//Xylophone
//Adapted for an ArduinoMega
//from Jenna deBoisblanc and Spiekenzie Labs initial code
#include "midiCode.h"


//*
  //*******************************************************************************************************************
  // User settable variables
  //*******************************************************************************************************************

  int pinRead;
  #define numberOfPins 8
  char pinAssignments[numberOfPins] ={
  A0,A1,A2,A3,A4,A5,A6,A7};
  byte PadNote[numberOfPins] = {
  57,41,59,60,61,62,63,64};         // MIDI notes from 0 to 127 (Mid C = 60)
  int PadCutOff[numberOfPins] =
  {
  400,400,200,800,400,400,400,400};           // Minimum Analog value to cause a drum hit

  int MaxPlayTime[numberOfPins] = {
  90,90,90,90,90,90,90,90};               // Cycles before a 2nd hit is allowed



  //*******************************************************************************************************************
  // Setup
  //*******************************************************************************************************************
  void setup()
  {
  setupMidi();

  }
  //*******************************************************************************************************************
  // Main Program
  //*******************************************************************************************************************
  void loop()
  {
  //*
  while(true){
    for(int i=0; i < 127; i++)
    {
      MIDI_TX(0x90,i,125);
    }
    delay(100);
  }
  //*/
  int forceHit = 0;
  for(int pin=0; pin < 7; pin++)                          //
  {
    forceHit = analogRead(pinAssignments[pin]);
    //Serial.println(forceHit);


    if((forceHit > PadCutOff[pin]))
    {
      turn_MIDI_note_on(PadNote[pin], pin, forceHit);
    }
    else
    {
      turn_MIDI_note_off(pin,PadNote[pin],MaxPlayTime[pin]);
    }
  }
  }
//*/

/*
  MIDI note player

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
  If this circuit is connected to a MIDI synth, it will play the notes
  F#-0 (0x1E) to F#-5 (0x5A) in sequence.

  The circuit:
  - digital in 1 connected to MIDI jack pin 5
  - MIDI jack pin 2 connected to ground
  - MIDI jack pin 4 connected to +5V through 220 ohm resistor
  - Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

  created 13 Jun 2006
  modified 13 Aug 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Midi
*/


/*
void setup() {
  // Set MIDI baud rate:
  Serial.begin(31250 );
}

void loop() {
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  for (int note = 0x1E; note < 0x5A; note ++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x45);
    delay(100);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x00);
    delay(100);
  }
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
*/

