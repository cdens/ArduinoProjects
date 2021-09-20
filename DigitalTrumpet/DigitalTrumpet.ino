
//whether or not to log to serial monitor
int logging = 0;

//valve button pins
const byte V1 = 10;
const byte V2 = 9;
const byte V3 = 8;

//controls whether or not the "trumpet" is playing
const byte SELECT = 11;

//reads voltage from potentiometer- determines which note to play for notes with multiple valve combinations (must be analog input)
const byte POT = A0;

//passes frequency for piezo buzzer to play (must be a PWM pin!)
const byte BUZZ = 6;

const int delayTime = 100; // refresh rate in ms

// stores valve positions and frequencies for all notes (including sharps/flats) from low G (G2) to high C (C5)
// format for each note: {valve 1, valve 2, valve 3, frequency (Hz)}
const int numNotes = 29;
int noteInfo[numNotes][4] = {
    {1,0,1,98}, //G2
    {0,1,1,104}, //G#2
    {1,1,0,110}, //A2
    {1,0,0,117}, //Bb2
    {0,1,0,123}, //B2
    {0,0,0,131}, //C3
    {1,1,1,139}, //C#3
    {1,0,1,147}, //D3
    {0,1,1,156}, //D#3
    {1,1,0,165}, //E3
    {1,0,0,175}, //F3
    {0,1,0,185}, //F#3
    {0,0,0,196}, //G3
    {0,1,1,208}, //G#3
    {1,1,0,220}, //A3
    {1,0,0,233}, //Bb3
    {0,0,0,262}, //C4 **upper octave fingerings are same as lower octave to ease use of the potentiometer to distinguish ambiguous notes
    {1,1,0,277}, //C#4
    {1,0,1,294}, //D4
    {0,1,1,311}, //D#4
    {1,1,0,330}, //E4
    {1,0,0,349}, //F4
    {0,1,0,370}, //F#4
    {0,0,0,392}, //G4
    {0,1,1,415}, //G#4
    {1,1,0,440}, //A4
    {1,0,0,466}, //Bb44
    {0,1,0,494}, //B4
    {0,0,0,523} //C5
  };



//plays the first line of twinkle twinkle little star
void soundTest() {
  
  //frequencies for twinkle twinkle little star
  const int TTLSfreqs[] = {262, 262, 392, 392, 440, 440, 392};
  
  int numTones = sizeof(TTLSfreqs)/2;
  int cdelay = 300;
  int enddelay = 700;
  
  for (int i = 0; i < numTones-1; i++) {
    tone(BUZZ, TTLSfreqs[i], cdelay);
    delay(cdelay);
  } 
  tone(BUZZ, TTLSfreqs[numTones-1], enddelay);
  delay(enddelay);
  noTone(BUZZ);
  delay(1000);
}



//set up pins, start serial monitor if necessary
void setup() {
  pinMode(V1,INPUT_PULLUP);
  pinMode(V2,INPUT_PULLUP);
  pinMode(V3,INPUT_PULLUP);
  pinMode(SELECT,INPUT_PULLUP);
  pinMode(POT, INPUT);
  pinMode(BUZZ, OUTPUT);
  if (logging) {  
    Serial.begin(9600);
  }

  // soundTest(); //test that sound works
}




//uses valve positions and potentiometer position to determine proper frequency to play from noteInfo array
int findFreqFromValveCombos(int v1, int v2, int v3, int potStatus) {
  int freqToPlay = 0; //default is 0: if valve position matches no correct positions nothing will play
  int potDiff = 10000; //used to find minimum difference between potentiometer position and frequency specified by valve combination
  int potFreq = map(potStatus, 0, 1023, noteInfo[0][3], noteInfo[numNotes-1][3]); //converts potentiometer position into frequency (Hz)
  int cpotdiff;

  //looping through each possible note, finding the frequency with a matching valve position closest to the potentiometer-specified frequency
  for (int i = 0; i < numNotes; i++) {
    cpotdiff = abs(potFreq - noteInfo[i][3]);
    if (v1 == noteInfo[i][0] && v2 == noteInfo[i][1] && v3 == noteInfo[i][2] && cpotdiff < potDiff) {
      freqToPlay = noteInfo[i][3];
      potDiff = cpotdiff;
    }
  }

  if (logging) {
    Serial.println("Selected frequency: " + String(freqToPlay) + " Hz, (potFreq=" + String(potFreq));
  }
  
  return freqToPlay;
}




void loop() {

  //get valve positions, potentiometer position and 'play-select' button position
  int valvestatus[] = {!digitalRead(V1), !digitalRead(V2), !digitalRead(V3)};
  int selectStatus = !digitalRead(SELECT);
  int potStatus = analogRead(POT);
  
  if (logging) {
    Serial.println("Current valve status: " + String(valvestatus[0]) + "-" + String(valvestatus[1]) + "-" + String(valvestatus[2]) + ", select=" + String(selectStatus) + ", pot=" + String(potStatus));
  }

  //determine ideal frequency to play
  int cfreq = findFreqFromValveCombos(valvestatus[0],valvestatus[1],valvestatus[2],potStatus);

  //play specified frequency or stop sound from buzzer
  if (cfreq && selectStatus) {
    tone(BUZZ, cfreq, delayTime+200); //delaytime + 200 prevents short drops in sound with each pass through loop()
  } else {
    noTone(BUZZ);
  }

  delay(delayTime);
}
