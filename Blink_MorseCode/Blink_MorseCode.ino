/*
  Blink_MorseCode
*/


// global variables: a array
int Amorse[] = {0,1};
int Bmorse[] = {1,0,0,0};
int Cmorse[] = {1,0,1,0};
int Dmorse[] = {1,0,0};
int Emorse[] = {0};
int Fmorse[] = {0,0,1,0};
int Gmorse[] = {1,1,0};
int Hmorse[] = {0,0,0,0};
int Imorse[] = {0,0};
int Jmorse[] = {0,1,1,1};
int Kmorse[] = {1,0,1};
int Lmorse[] = {0,1,0,0};
int Mmorse[] = {1,1};
int Nmorse[] = {1,0};
int Omorse[] = {1,1,1};
int Pmorse[] = {0,1,1,0};
int Qmorse[] = {1,1,0,1};
int Rmorse[] = {0,1,0};
int Smorse[] = {0,0,0};
int Tmorse[] = {1};
int Umorse[] = {0,0,1};
int Vmorse[] = {0,0,0,1};
int Wmorse[] = {0,1,1};
int Xmorse[] = {1,0,0,1};
int Ymorse[] = {1,0,1,1};
int Zmorse[] = {1,1,0,0};
int morse1[] = {0,1,1,1,1};
int morse2[] = {0,0,1,1,1};
int morse3[] = {0,0,0,1,1};
int morse4[] = {0,0,0,0,1};
int morse5[] = {0,0,0,0,0};
int morse6[] = {1,0,0,0,0};
int morse7[] = {1,1,0,0,0};
int morse8[] = {1,1,1,0,0};
int morse9[] = {1,1,1,1,0};
int morse0[] = {1,1,1,1,1};
int invalidsequence[] = {2,2,2,2,2};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin (9600);
}

// returns the morse code sequence (1=dash,0=dot) for a letter
// sequence will always be 5 digits long, with unused digits set to 2
// if a lowercase letter isn"t given, an array of 5 2's will be returned
void getMorseSequence(int * sequence, const char letter) {

  String strletter = String(letter);
  memcpy(sequence, invalidsequence, sizeof(invalidsequence)); //clears previous sequence
  
  if (strletter.equals("a")) {
      memcpy(sequence, Amorse, sizeof(Amorse));
    } else if (strletter.equals("b")) {
      memcpy(sequence, Bmorse, sizeof(Bmorse));
    } else if (strletter.equals("c")) {
      memcpy(sequence, Cmorse, sizeof(Cmorse));
    } else if (strletter.equals("d")) {
      memcpy(sequence, Dmorse, sizeof(Dmorse));
    } else if (strletter.equals("e")) {
      memcpy(sequence, Emorse, sizeof(Emorse));
    } else if (strletter.equals("f")) {
      memcpy(sequence, Fmorse, sizeof(Fmorse));
    } else if (strletter.equals("g")) {
      memcpy(sequence, Gmorse, sizeof(Gmorse));
    } else if (strletter.equals("h")) {
      memcpy(sequence, Hmorse, sizeof(Hmorse));
    } else if (strletter.equals("i")) {
      memcpy(sequence, Imorse, sizeof(Imorse));
    } else if (strletter.equals("j")) {
      memcpy(sequence, Jmorse, sizeof(Jmorse));
    } else if (strletter.equals("k")) {
      memcpy(sequence, Kmorse, sizeof(Kmorse));
    } else if (strletter.equals("l")) {
      memcpy(sequence, Lmorse, sizeof(Lmorse));
    } else if (strletter.equals("m")) {
      memcpy(sequence, Mmorse, sizeof(Mmorse));
    } else if (strletter.equals("n")) {
      memcpy(sequence, Nmorse, sizeof(Nmorse));
    } else if (strletter.equals("o")) {
      memcpy(sequence, Omorse, sizeof(Omorse));
    } else if (strletter.equals("p")) {
      memcpy(sequence, Pmorse, sizeof(Pmorse));
    } else if (strletter.equals("q")) {
      memcpy(sequence, Qmorse, sizeof(Qmorse));
    } else if (strletter.equals("r")) {
      memcpy(sequence, Rmorse, sizeof(Rmorse));
    } else if (strletter.equals("s")) {
      memcpy(sequence, Smorse, sizeof(Smorse));
    } else if (strletter.equals("t")) {
      memcpy(sequence, Tmorse, sizeof(Tmorse));
    } else if (strletter.equals("u")) {
      memcpy(sequence, Umorse, sizeof(Umorse));
    } else if (strletter.equals("v")) {
      memcpy(sequence, Vmorse, sizeof(Vmorse));
    } else if (strletter.equals("w")) {
      memcpy(sequence, Wmorse, sizeof(Wmorse));
    } else if (strletter.equals("x")) {
      memcpy(sequence, Xmorse, sizeof(Xmorse));
    } else if (strletter.equals("y")) {
      memcpy(sequence, Ymorse, sizeof(Ymorse));
    } else if (strletter.equals("z")) {
      memcpy(sequence, Zmorse, sizeof(Zmorse));
    } else if (strletter.equals("1")) {
      memcpy(sequence, morse1, sizeof(morse1));
    } else if (strletter.equals("2")) {
      memcpy(sequence, morse2, sizeof(morse2));
    } else if (strletter.equals("3")) {
      memcpy(sequence, morse3, sizeof(morse3));
    } else if (strletter.equals("4")) {
      memcpy(sequence, morse4, sizeof(morse4));
    } else if (strletter.equals("5")) {
      memcpy(sequence, morse5, sizeof(morse5));
    } else if (strletter.equals("6")) {
      memcpy(sequence, morse6, sizeof(morse6));
    } else if (strletter.equals("7")) {
      memcpy(sequence, morse7, sizeof(morse7));
    } else if (strletter.equals("8")) {
      memcpy(sequence, morse8, sizeof(morse8));
    } else if (strletter.equals("9")) {
      memcpy(sequence, morse9, sizeof(morse9));
    } else if (strletter.equals("0")) {
      memcpy(sequence, morse0, sizeof(morse0));
    }
    
}

// the loop function runs over and over again forever
void loop() {
  // string to print in morse code on LED
  char printString[] = "hannah";
  int lenPrintString = strlen(printString);

  //starting with rapid 2 sec blink then 2 seconds off
  for (int i = 0; i < 20; i++) {
  digitalWrite(LED_BUILTIN, HIGH); //LED ON
  delay(50);
  digitalWrite(LED_BUILTIN, LOW); //LED OFF
  delay(50);
  }
  delay(2000);
  
  // establishes time to blink between dashes and dots (in ms)
  int dotOnTime = 125; 
  int dotOffTime = 125; 
  int dashOnTime = 375;
  int dashOffTime = 125;
  int timeBetweenLetters = 1000; // 1 second between letters
  int timeBetweenMessages = 2000; // 2 seconds between completed message
  int currentSequence[] = {2,2,2,2,2};
  
  // looping through letters in printString, determining and displaying flashing sequence, then pausing for 2 seconds before looping 
  for (int i = 0; i < lenPrintString; i++) {
    getMorseSequence(currentSequence, printString[i]);
    Serial.print("Letter: " + String(printString[i]) + ", sequence = ");
    for (int l = 0; l < 5; l++) {
      if (currentSequence[l] == 0) {
        digitalWrite(LED_BUILTIN, HIGH); //LED ON
        delay(dotOnTime);
        digitalWrite(LED_BUILTIN, LOW); //LED OFF
        delay(dotOffTime);
        } else if (currentSequence[l] == 1) {
        digitalWrite(LED_BUILTIN, HIGH); //LED ON
        delay(dashOnTime);
        digitalWrite(LED_BUILTIN, LOW); //LED OFF
        delay(dashOffTime);
        }

        if (currentSequence[l] < 2) {
          Serial.print(currentSequence[l]); Serial.print(" ");
        }
      }

    //pause between letters
    Serial.print("\n");
    delay(timeBetweenLetters);
    }

  //pause between completed message
  delay(timeBetweenMessages);
  Serial.end();
}
