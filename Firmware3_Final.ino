#include <MIDIUSB.h>

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

byte inputsManual1[] = {22,23,24,25,26,27,28,29};          //Deklariere inputs und outputs
byte inputsManual2[] = {38,39,40,41,42,43,44,45};         
byte inputsPedal1[] = {A2, A3, A4, A5, A6, A7, A8, A9}; 

#define inCountManual1 sizeof(inputsManual1)/sizeof(inputsManual1[0])
#define inCountManual2 sizeof(inputsManual2)/sizeof(inputsManual2[0])
#define inCountPedal1 sizeof(inputsManual2)/sizeof(inputsPedal1[0])

byte outputsManual1[] = {30,31,32,33,34,35,36,37};
byte outputsManual2[] = {46,47,48,49,50,51,52,53};
byte outputsPedal1[] = {A0, A1};

#define outCountManual1 sizeof(outputsManual1)/sizeof(outputsManual1[0])
#define outCountManual2 sizeof(outputsManual2)/sizeof(outputsManual2[0])
#define outCountPedal1 sizeof(outputsPedal1)/sizeof(outputsPedal1[0])

int layout[outCountManual1][inCountManual1] = {               //layout grid for Manuals
  //Manual 1+2
  {48,47,46,45,44,43,42,41},
  {56,55,54,53,52,51,50,49},
  {64,63,62,61,60,59,58,57},
  {72,71,70,69,68,67,66,65},
  {80,79,78,77,76,75,74,73},
  {88,87,86,85,84,83,82,81},
  {97,96,95,94,93,92,91,89},
  {105,104,103,102,101,100}
};

int layoutPedal[outCountPedal1][inCountPedal1] = {               //layout grid for Pedal
  //Manual 1+2
  {52,51,50,49,48,0,0,0},
  {60,59,58,57,56,55,54,53}
  };

int keyDownManual1[outCountManual1][inCountManual1];
bool keyLongManual1[outCountManual1][inCountManual1];
int keyDownManual2[outCountManual2][inCountManual2];
bool keyLongManual2[outCountManual2][inCountManual2];
int keyDownPedal1[outCountPedal1][inCountPedal1];
bool keyLongPedal1[outCountPedal1][inCountPedal1];



/**** Funktionen für MIDI ***************************************************/

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
    noteOnPedal(3, midisig, 127);  
    MidiUSB.flush();
    tasteAlt = taste;
    delayMicroseconds(500);
    return tasteAlt;
  }

  if(tasteAlt == LOW && taste == HIGH){
    noteOffPedal(3, midisig, 127);  
    MidiUSB.flush();
    tasteAlt = taste;
    delayMicroseconds(500);
    return tasteAlt;
  }
}

void noteOnPedal(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOffPedal(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
  
void setup(){
  //Pins für Pedaltasten
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
    
  for(int i=0; i<outCountManual1; i++){    //declaring all the outputs and setting them high
    pinMode(outputsManual1[i],OUTPUT);
    digitalWrite(outputsManual1[i],HIGH);
    pinMode(outputsManual2[i],OUTPUT);
    digitalWrite(outputsManual2[i],HIGH);

  }
  for(int i=0; i<inCountManual2; i++){     //declaring all the inputs and activating the internal pullup resistor
    pinMode(inputsManual1[i],INPUT_PULLUP);
    pinMode(inputsManual2[i],INPUT_PULLUP);
  }

    for(int i=0; i<outCountPedal1; i++){    //declaring all the outputs and setting them high
    pinMode(outputsPedal1[i],OUTPUT);
    digitalWrite(outputsPedal1[i],HIGH);
  }
  for(int i=0; i<inCountPedal1; i++){     //declaring all the inputs and activating the internal pullup resistor
    pinMode(inputsPedal1[i],INPUT_PULLUP);
  }

  //Serial.begin(9600);               //establishing Serial link and initializing keyboard
  //Serial.println("Connected");
}

//Main loop going through all the keys, then waiting 0.5ms
void loop() {
  taste1Alt = MidiButton(2, 36, taste1Alt);
  taste2Alt = MidiButton(3, 37, taste2Alt);
  taste3Alt = MidiButton(4, 38, taste3Alt);
  taste4Alt = MidiButton(5, 39, taste4Alt);
  taste5Alt = MidiButton(6, 40, taste5Alt);
  taste6Alt = MidiButton(7, 41, taste6Alt);
  taste7Alt = MidiButton(8, 42, taste7Alt);
  taste8Alt = MidiButton(9, 43, taste8Alt);
  taste9Alt = MidiButton(10, 44, taste9Alt);
  taste10Alt = MidiButton(11, 45, taste10Alt);
  taste11Alt = MidiButton(12, 46, taste11Alt);
  taste12Alt = MidiButton(13, 47, taste12Alt);
  
  //Manuall 1
  for (int i=0; i<outCountManual1; i++)
  {    
    digitalWrite(outputsManual1[i],LOW);   //setting one row low
    delayMicroseconds(5);           //giving electronics time to settle down
    
    for(int j=0; j<inCountManual1; j++)
    {
      if(digitalRead(inputsManual1[j]) == LOW)
      {
        keyPressedManual1(i,j, 1);            //calling keyPressed function if one of the inputs reads low
      }
      else if(keyDownManual1[i][j] != 0)   //resetting the key if it is not pressed any more
      {  
        resetKeyManual1(i,j, 1);
      }
    }

    digitalWrite(outputsManual1[i],HIGH);
    delayMicroseconds(500);         //setting the row high and waiting 0.5ms until next cycle
  }

  //Manuall 2
  for (int i=0; i<outCountManual2; i++)
  {    
    digitalWrite(outputsManual2[i],LOW);   //setting one row low
    delayMicroseconds(5);           //giving electronics time to settle down
    
    for(int j=0; j<inCountManual2; j++)
    {
      if(digitalRead(inputsManual2[j]) == LOW)
      {
        keyPressedManual2(i,j, 2);            //calling keyPressed function if one of the inputs reads low
      }
      else if(keyDownManual2[i][j] != 0)   //resetting the key if it is not pressed any more
      {  
        resetKeyManual2(i,j, 2);
      }
    }

    digitalWrite(outputsManual2[i],HIGH);
    delayMicroseconds(500);         //setting the row high and waiting 0.5ms until next cycle
  }
    
  //Pedal 1
  for (int i=0; i<outCountPedal1; i++)
  {    
    digitalWrite(outputsPedal1[i],LOW);   //setting one row low
    delayMicroseconds(5);           //giving electronics time to settle down
    
    for(int j=0; j<inCountPedal1; j++)
    {
      if(digitalRead(inputsPedal1[j]) == LOW)
      {
        keyPressedPedal1(i,j, 3);            //calling keyPressed function if one of the inputs reads low
      }
      else if(keyDownPedal1[i][j] != 0)   //resetting the key if it is not pressed any more
      {  
        resetKeyPedal1(i,j, 3);
      }
    }

    digitalWrite(outputsPedal1[i],HIGH);
    delayMicroseconds(500);         //setting the row high and waiting 0.5ms until next cycle
  }
}


// ==============
// == Manual 1 ==
// ==============
//if a key is pressed, this Funtion is called and outputs to serial the key location, it also sends the keystroke if not already done so
void keyPressedManual1(int row, int col, int kanal){

  if(keyDownManual1[row][col]==0){         //if the function is called for the first time for this key
    int kanal = 1;
    noteOn(kanal, layout[row][col], 127);  
    MidiUSB.flush();
  }

  keyDownManual1[row][col]++;
}

void resetKeyManual1(int row, int col, int kanal){ //resetting the variables after key is released
  keyDownManual1[row][col] = 0;
  keyLongManual1[row][col] = false;
  noteOff(kanal, layout[row][col], 127);  
  MidiUSB.flush();

}

// ==============
// == Manual 2 ==
// ==============
void keyPressedManual2(int row, int col, int kanal){

  if(keyDownManual2[row][col]==0){         //if the function is called for the first time for this key
    noteOn(kanal, layout[row][col], 127);  
    MidiUSB.flush();
  }

  keyDownManual2[row][col]++;
}

void resetKeyManual2(int row, int col, int kanal){ //resetting the variables after key is released
  keyDownManual2[row][col] = 0;
  keyLongManual2[row][col] = false;
  noteOff(kanal, layout[row][col], 127);  
  MidiUSB.flush();

}

// =============
// == Pedal 1 ==
// =============
void keyPressedPedal1(int row, int col, int kanal){

  if(keyDownPedal1[row][col]==0){         //if the function is called for the first time for this key
    noteOn(kanal, layoutPedal[row][col], 127);  
    MidiUSB.flush();
  }

  keyDownPedal1[row][col]++;
}

void resetKeyPedal1(int row, int col, int kanal){ //resetting the variables after key is released
  keyDownPedal1[row][col] = 0;
  keyLongPedal1[row][col] = false;
  noteOff(kanal, layoutPedal[row][col], 127);  
  MidiUSB.flush();

}
