#define  midichannel 1;                              // MIDI channel from 0 to 15 (+1 in "real world")
bool VelocityFlag  = true;                           // Velocity ON (true) or OFF (false)
#include "Arduino.h"

//*******************************************************************************************************************
// Internal Use Variables
//*******************************************************************************************************************
bool activePad[7] = {
  0,0,0,0,0,0,0};                   // Array of flags of pad currently playing
int PinPlayTime[7] = {
  0,0,0,0,0,0,0};                     // Counter since pad started to play
  

void setupMidi()
{
  Serial.begin(31250);                                  // SET HAIRLESS TO THE SAME BAUD RATE IN THE SETTINGS
}



//*******************************************************************************************************************
// Transmit MIDI Message
//*******************************************************************************************************************
void MIDI_TX(byte MESSAGE, byte PITCH, byte VELOCITY) 
{
  static byte status1;

  //Serial.println("got a message");
  status1 = MESSAGE + midichannel;
  Serial.write(status1);
  Serial.write(PITCH);
  Serial.write(VELOCITY);

}


void turn_MIDI_note_off(char pin,byte padNote,  int MaxPlayTime)
{
  if((activePad[pin] == true))
  {
    PinPlayTime[pin] = PinPlayTime[pin] + 1;
    if(PinPlayTime[pin] > MaxPlayTime)
    {
      activePad[pin] = false;
      MIDI_TX(144,padNote,0); 
    }
  }
}

void turn_MIDI_note_on(char pin, char pinNumber,  int forceHit)
{
  if((activePad[pinNumber] == false))
  {
    if(VelocityFlag == true)
    {
      //          hitavg = 127 / ((1023 - PadCutOff[pin]) / (hitavg - PadCutOff[pin]));    // With full range (Too sensitive ?)
      forceHit = (forceHit / 8) -1 ;                                                 // Upper range
    }
    else
    {
      forceHit = 127;
    }
    MIDI_TX(144,pin,forceHit); //note on

    PinPlayTime[pinNumber] = 0;
    activePad[pinNumber] = true;
  }
  else
  {
    PinPlayTime[pinNumber] = PinPlayTime[pinNumber] + 1;
  }
}
