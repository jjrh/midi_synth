#include <MIDI.h>

const int channel = 1;
unsigned long t=0;

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(57600);
  Serial.println("MIDI Input Test");

}

void loop(){
  midi_input();
  //  output();
  //  delay(2000);

}

void midi_input() {
  int type, note, velocity, channel, d1, d2;
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    Serial.println("midi read\n");
    byte type = MIDI.getType();
    switch (type) {
      case NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        if (velocity > 0) {
          Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        } else {
          Serial.println(String("Note Off: ch=") + channel + ", note=" + note);
        }
        break;
      case NoteOff:
        note = MIDI.getData1();
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
