#include <MIDIUSB.h>

//Variablen für Pedaltasten
bool taste0Alt = LOW;
bool taste1Alt = LOW;
bool taste2Alt = LOW;
bool taste3Alt = LOW;
bool taste4Alt = LOW;
bool taste5Alt = LOW;
bool taste6Alt = LOW;
bool taste7Alt = LOW;
bool taste8Alt = LOW;
bool taste9Alt = LOW;
bool taste10Alt = LOW;
bool taste11Alt = LOW;
bool taste12Alt = LOW;
bool taste13Alt = LOW;
bool taste14Alt = LOW;
bool taste15Alt = LOW;
bool taste16Alt = LOW;
bool taste17Alt = LOW;
bool taste18Alt = LOW;

//Variablen für Register
bool register1 = false;
bool register2 = false;
bool register3 = false;
bool register4 = false;
bool register5 = false;
bool register6 = false;
bool register7 = false;
bool register8 = false;
bool register9 = false;
bool register10 = false;
bool register11 = false;
bool register12 = false;
bool register13 = false;


/**** Funktionen für MIDI ***************************************************/
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

bool MidiButton(int pin, byte midisig, bool tasteAlt) {      //Button-Pin, Noten-Nummer
  bool taste = digitalRead(pin);
  if(tasteAlt == HIGH && taste == LOW){
    noteOn(0, midisig, 64);  
    MidiUSB.flush();
    tasteAlt = taste;
    delay(100);
    return tasteAlt;
  }

  if(tasteAlt == LOW && taste == HIGH){
    noteOff(0, midisig, 64);  
    MidiUSB.flush();
    tasteAlt = taste;
    delay(100);
    return tasteAlt;
  }
}

bool RegisterButton(int pin, byte midisig, bool registerAlt) {      //Button-Pin, Noten-Nummer
  bool registerTemp = digitalRead(pin);
  if(registerAlt == true && registerTemp == false) {
    controlChange(0, midisig, 127); //Register an
    registerAlt = false;
    delay(100);
    return registerAlt;
  }
  if(registerAlt == false && registerTemp == true) {
    controlChange(0, midisig, 0); //Register aus
    registerAlt = true;
    delay(100);
    return registerAlt;
  }
}

/****************************************************************************/

void setup() {
  //Pins für Pedaltasten
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);

  //Pins für Register
  pinMode(41, INPUT_PULLUP);
  pinMode(42, INPUT_PULLUP);
  pinMode(43, INPUT_PULLUP);
  pinMode(44, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(46, INPUT_PULLUP);
  pinMode(47, INPUT_PULLUP);
  pinMode(48, INPUT_PULLUP);
  pinMode(49, INPUT_PULLUP);
  pinMode(50, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(52, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);
  
}

void loop() {
  //Pedaltasten
  taste0Alt = MidiButton(22, 41, taste0Alt);
  taste1Alt = MidiButton(23, 42, taste1Alt);
  taste2Alt = MidiButton(24, 43, taste2Alt);
  taste3Alt = MidiButton(25, 44, taste3Alt);
  taste4Alt = MidiButton(26, 45, taste4Alt);
  taste5Alt = MidiButton(27, 46, taste5Alt);
  taste6Alt = MidiButton(28, 47, taste6Alt);
  taste7Alt = MidiButton(29, 48, taste7Alt);
  taste8Alt = MidiButton(30, 49, taste8Alt);
  taste9Alt = MidiButton(31, 50, taste9Alt);
  taste10Alt = MidiButton(32, 51, taste10Alt);
  taste11Alt = MidiButton(33, 52, taste11Alt);
  taste12Alt = MidiButton(34, 53, taste12Alt);
  taste13Alt = MidiButton(35, 54, taste13Alt);
  taste14Alt = MidiButton(36, 55, taste14Alt);
  taste15Alt = MidiButton(37, 56, taste15Alt);
  taste16Alt = MidiButton(38, 57, taste16Alt);
  taste17Alt = MidiButton(39, 58, taste17Alt);
  taste18Alt = MidiButton(40, 59, taste18Alt);

  //Register 1
  register1 = RegisterButton(41, 1, register1);
  register2 = RegisterButton(42, 2, register2);
  register3 = RegisterButton(43, 3, register3);
  register4 = RegisterButton(44, 4, register4);
  register5 = RegisterButton(45, 5, register5);
  register6 = RegisterButton(46, 6, register6);
  register7 = RegisterButton(47, 7, register7);
  register8 = RegisterButton(48, 8, register8);
  register9 = RegisterButton(49, 9, register9);
  register10 = RegisterButton(50, 10, register10);
  register11 = RegisterButton(51, 11, register11);
  register12 = RegisterButton(52, 12, register12);
  register13 = RegisterButton(53, 13, register13);
  

}
