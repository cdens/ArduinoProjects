
/*
RGB_nightlight
This project uses an Arduino Uno, an RGB LED, and a photoresistor to create a nightlight that moves through a spectrum of colors.
On startup, the photoresistor detects the ambient light in the room, and when the light is turned off, it will activate the light. 
To reset the value for ambient light in a room, restart the script with the reset button on the arduino. 
 */


int logging = 1; // 1 to log to serial, 0 to not log

// pins for different colors (output)
byte REDPIN = 9;
byte BLUEPIN = 10;
byte GREENPIN = 11;

// pin for the photoresistor (read voltage -> light level)
byte READ_PR = A0;

// variables to store color threshold and target value
int calibrationLightLevel;
int currentLightLevel;

const int colormapLength = 100; //length of the colormap to create
int currentIndex = -1; //current color to show
int colorsIncreasing = 1; //1 if increasing through colormap, -1 if decreasing

const int colorPeriod = 10; // period (seconds) for the colormap to complete (start to finish to start)
const int delayTimeMs = colorPeriod * 1000 / colormapLength; // delay time in ms between each color change

//arrays for red/green/blue colormap values
byte red[colormapLength];
byte green[colormapLength];
byte blue[colormapLength];

byte noOverflowIterate(byte val, byte iterAmount, int byteIncreasing) {
  if (byteIncreasing == 1) {
      if (val+iterAmount > 255) {
        val = 255;
      } else {
        val += iterAmount;
      }
    } else if (byteIncreasing == 0) {
      if (val-iterAmount < 0) {
        val = 0;
      } else {
        val -= iterAmount;
      }
    }
  return val;
}

//fills a red/green/blue arrays with a jet colormap
void makeJetColormapArrays(byte * red, byte * green, byte * blue, int numPoints) {

  //parameters to build colormap
  byte iterateColorVal = 255*numPoints/2500;
  
  //calculating array indices to start each color transition
  int startGreenInc = 0.125*numPoints;
  int startRedIncBlueDec = 0.38*numPoints;
  int startGreenDec = 0.63*numPoints;
  int startRedDec = 0.88*numPoints;
  
  //initializing colors: starting with blue color, blue amount increasing
  byte r = 0;
  byte g = 0;
  byte b = 130;
  byte dr = 0;
  byte dg = 0;
  byte db = iterateColorVal;
  int rinc = 1;
  int ginc = 1;
  int binc = 1;

  //filling array
  for (int i = 0; i < numPoints; i++) {

    //if at a transition point, adjust values
    if (i == startGreenInc) {
      b = 255;
      db = 0;
      dg = iterateColorVal;
    } else if (i == startRedIncBlueDec) {
      g = 255;
      dg = 0;
      db = iterateColorVal;
      dr = iterateColorVal;
      binc = 0;
    } else if (i == startGreenDec) {
      r = 255;
      b = 0;
      dr = 0;
      db = 0;
      dg = iterateColorVal;
      ginc = 0;
    } else if (i == startRedDec) {
      dg = 0;
      g = 0;
      dr = iterateColorVal;
      rinc = 0;
    }

    //iterating each color (taking care to prevent overflow)
    r = noOverflowIterate(r, dr, rinc);
    g = noOverflowIterate(g, dg, ginc);
    b = noOverflowIterate(b, db, binc);

    //writing colors to arrays
    red[i] = r;
    green[i] = g;
    blue[i] = b;
    
  }
}

void setColor(byte red, byte green, byte blue) {
  analogWrite(REDPIN, red);
  analogWrite(BLUEPIN, blue);
  analogWrite(GREENPIN, green);
}

void setTestColor() {
  //byte color[] = {255,0,0}; //red
  //byte color[] = {0,0,255}; //blue
  //byte color[] = {0,255,0}; //green
  //byte color[] = {100,0,130}; //purple
  //byte color[] = {255,255,5}; //yellow
  //byte color[] = {255,255,255}; //white
  //setColor(color[0],color[1],color[2]);
}

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(READ_PR, INPUT);
  currentLightLevel = analogRead(READ_PR);
  calibrationLightLevel = 0.8 * currentLightLevel; // threshold for darkness is 3/4 of ambient light

  if (logging) {
    Serial.begin (9600);
    Serial.println("Delay time (ms): " + String(delayTimeMs));
    Serial.println("Ambient light (V-int): " + String(currentLightLevel));
    Serial.println("Light calibration (V-int): " + String(calibrationLightLevel));
  }

  //initializing global colormap variables
  makeJetColormapArrays(red, green, blue, colormapLength);
}



void loop() {

  currentIndex += colorsIncreasing;
  if (currentIndex >= colormapLength) {
    currentIndex = colormapLength - 1;
    colorsIncreasing = -1;
  } else if (currentIndex < 0) {
    currentIndex = 0;
    colorsIncreasing = 1;
  }

  

  //checking for darkness and updating the color (or turning off), waiting for specified delay time to continue
  currentLightLevel = analogRead(READ_PR);

  if (logging) {
    Serial.println("Current light level (V-int): " + String(currentLightLevel));
  }
  
  if (currentLightLevel <= calibrationLightLevel) {
    setColor(red[currentIndex],green[currentIndex],blue[currentIndex]);
    
    if (logging) {
      Serial.println("Setting color: r=" + String(red[currentIndex]) + ", g=" + String(green[currentIndex]) + ", b=" + String(blue[currentIndex]));
    }
    
  } else {
    setColor(0,0,0);
  }
  
  delay(delayTimeMs);
}
