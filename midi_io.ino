#include <MIDI.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "midi_notes.h"



// GUItool: begin automatically generated code
/* AudioSynthWaveform       waveform1;      //xy=188,240 */
/* AudioEffectEnvelope      envelope1;      //xy=371,237 */
/* AudioOutputI2S           i2s1;           //xy=565,241 */
/* AudioConnection          patchCord1(waveform1, envelope1); */
/* AudioConnection          patchCord2(envelope1, 0, i2s1, 0); */
/* AudioConnection          patchCord3(envelope1, 0, i2s1, 1); */

// GUItool: end automatically generated code

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform4;      //xy=152,324
AudioSynthWaveform       waveform2;      //xy=154,227
AudioSynthWaveform       waveform3;      //xy=154,273
AudioSynthWaveform       waveform1;      //xy=156,183
AudioEffectEnvelope      envelope4;      //xy=332,351
AudioEffectEnvelope      envelope3;      //xy=338,270
AudioEffectEnvelope      envelope2;      //xy=340,209
AudioEffectEnvelope      envelope1;      //xy=341,164
AudioMixer4              mixer1;         //xy=532,221
AudioOutputI2S           i2s1;           //xy=711,221
AudioConnection          patchCord1(waveform4, envelope4);
AudioConnection          patchCord2(waveform2, envelope2);
AudioConnection          patchCord3(waveform3, envelope3);
AudioConnection          patchCord4(waveform1, envelope1);
AudioConnection          patchCord5(envelope4, 0, mixer1, 3);
AudioConnection          patchCord6(envelope3, 0, mixer1, 2);
AudioConnection          patchCord7(envelope2, 0, mixer1, 1);
AudioConnection          patchCord8(envelope1, 0, mixer1, 0);
AudioConnection          patchCord9(mixer1, 0, i2s1, 0);
AudioConnection          patchCord10(mixer1, 0, i2s1, 1);

AudioControlSGTL5000     audioShield;     //xy=586,175
// GUItool: end automatically generated code





const int channel = 1;
unsigned long t=0;

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(57600);
  Serial.println("MIDI Input Test");

  Serial.println("setup done");

  // Set up
  AudioMemory(8);
  audioShield.enable();
  audioShield.volume(0.45);

  waveform1.pulseWidth(0.5);
  waveform1.begin(0.4, 220, WAVEFORM_PULSE);

  waveform2.pulseWidth(0.5);
  waveform2.begin(0.4, 220, WAVEFORM_PULSE);

  waveform3.pulseWidth(0.5);
  waveform3.begin(0.4, 220, WAVEFORM_PULSE);

  waveform4.pulseWidth(0.5);
  waveform4.begin(0.4, 220, WAVEFORM_PULSE);


  envelope1.attack(50);
  envelope1.decay(50);
  envelope1.release(250);

  envelope2.attack(50);
  envelope2.decay(50);
  envelope2.release(250);

  envelope3.attack(50);
  envelope3.decay(50);
  envelope3.release(250);

  envelope4.attack(50);
  envelope4.decay(50);
  envelope4.release(250);
}

void loop(){
  /* float w; */
  /* for (uint32_t i =1; i<20; i++) { */
  /*   w = i / 20.0; */
  /*   Serial.print(w); */
  /*   Serial.println(); */
  /*   waveform1.pulseWidth(w); */
  /*   envelope1.noteOn(); */
  /*   delay(800); */
  /*   envelope1.noteOff(); */
  /*   delay(600); */
  /* } */


  midi_input();
  //  output();
  //  delay(2000);

}

const int state_length = 4;
int state[state_length];
int state_count =0;

void synth_note_on(int midi_inp){
  float note = notes[midi_inp];
  Serial.print("notes[");
  Serial.print(midi_inp);
  Serial.print("] =");
  Serial.print(notes[midi_inp]);
  Serial.println();
  for(int i=0; i<state_length; i++){
    if(state[i] ==0){
      switch (i) {
      case 0:
	envelope1.noteOn();
	waveform1.frequency(note);
	state[i]=midi_inp;
	i=state_length+1;
	break;
      case 1:
	envelope2.noteOn();
	waveform2.frequency(note);
	state[i]=midi_inp;
	i=state_length+1;
	break;
      case 2:
	envelope3.noteOn();
	waveform3.frequency(note);
	state[i]=midi_inp;
	i=state_length+1;
	break;
      case 3:
	envelope4.noteOn();
	waveform4.frequency(note);
	state[i]=midi_inp;
	i=state_length+1;
	break;
      default:
	break;

      }
    }
  }
}

void synth_note_off(int midi_inp){
  float note = notes[midi_inp];
  Serial.print("notes[");
  Serial.print(midi_inp);
  Serial.print("] =");
  Serial.print(notes[midi_inp]);
  Serial.println();
  for(int i=0; i<state_length; i++){
    if(state[i] ==midi_inp){
      switch (i) {
      case 0:
	envelope1.noteOff();
	waveform1.frequency(note);
	state[i]=0;
	i=state_length+1;
	break;
      case 1:
	envelope2.noteOff();
	waveform2.frequency(note);
	state[i]=0;
	i=state_length+1;
	break;
      case 2:
	envelope3.noteOff();
	waveform3.frequency(note);
	state[i]=0;
	i=state_length+1;
	break;
      case 3:
	envelope4.noteOff();
	waveform4.frequency(note);
	state[i]=0;
	i=state_length+1;
	break;
      default:
	break;

      }
    }
  }
}




void midi_input() {
  int type, note, velocity, channel, d1, d2;
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    Serial.println("midi read\n");
    byte type = MIDI.getType();
    switch (type) {
      case NoteOn:
        note = MIDI.getData1();
	synth_note_on(note);
	/* waveform1.frequency(notes[note]); */
	/* envelope1.noteOn(); */
	/* waveform1.noteOn(); */

        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        if (velocity > 0) {
          Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        } else {
          Serial.println(String("Note Off: ch=") + channel + ", note=" + note);
        }
        break;
      case NoteOff:

	/* envelope1.noteOff(); */
        note = MIDI.getData1();
	synth_note_off(note);
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        Serial.println(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        break;
    default:
        d1 = MIDI.getData1();
        d2 = MIDI.getData2();
        Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
    }
    t = millis();
  }
  if (millis() - t > 10000) {
    t += 10000;
    Serial.println("(inactivity)");
  }
}

void output(){
  int note;
  for (note=10; note <= 127; note++) {
    MIDI.sendNoteOn(note, 100, channel);
    Serial.print(note);
    Serial.print(" ");
    Serial.print(100);
    Serial.print(" ");
    Serial.println(channel);
    delay(200);
    MIDI.sendNoteOff(note, 100, channel);
  }

}
