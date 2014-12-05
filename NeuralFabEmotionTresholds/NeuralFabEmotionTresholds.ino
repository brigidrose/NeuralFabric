#include "Brainy.h"
#include "BrainPicker.h"
#include "RainbowOutput.h"
#include <math.h>

//Four horsemen of the meanpocolpyse
float annoyedMean;
float contentMean;
float dayDreamMean;
float focusedMean;

//The count master daddy
int meanCounter;

long interval = 1000; 
long previousMillis = 0;

InternalState internalState;

float val = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;


void setup() {
  incomingByte = 0;
  bufferIndex = 0;
  packetSize = 0;
  parseState = BEGIN;

  //Initialize and set horsemen to 0
  annoyedMean = 0;
  contentMean = 0;
  dayDreamMean = 0;
  focusedMean = 0;

  meanCounter = 0;

  internalState = NONE;

  Serial.begin(57600);	// opens serial port, sets data rate to 9600 bps

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
  pickMyBrain(brainActivity);
}


void brainActivity(Brainy &brain) {
  float deltaValue = brain.readDelta();
  float highBetaValue = brain.readHighBeta();
  float lowGammaValue = brain.readLowGamma();
  float lowAlphaValue = brain.readLowAlpha();
  
  meanCounter++;
  
  dayDreamMean = dayDreamMean + highBetaValue;
  contentMean = contentMean + deltaValue;
  focusedMean = focusedMean + lowGammaValue;
  annoyedMean = annoyedMean + lowAlphaValue;
  
  //First print the mean OF DELTA
  Serial.println("The mean of delta / content / green is......");
  float meanOfDelta = contentMean/meanCounter;
  Serial.println(meanOfDelta);
  Serial.println("-----------------------");
  
  //Print the mean OF HIGH BETA
  Serial.println("The mean of High beta / day dream / white is......");
  float meanOfHighBeta = dayDreamMean/meanCounter;
  Serial.print("mean of HB = ");
  Serial.println(meanOfHighBeta);
  Serial.println("-----------------------");
  
  //Print the mean OF HIGH BETA
  //notbeta
  Serial.println("The mean of Low gamma / focused / blue is......");
  float meanOfLowGamma = focusedMean/meanCounter;
  Serial.println(meanOfLowGamma);
  Serial.println("-----------------------");
  
  //Print the mean OF HIGH BETA
  //notbeta
  Serial.println("The mean of Low alpha / annoyed / red is......");
  float meanOfLowAlpha = annoyedMean/meanCounter;
  Serial.println(meanOfLowAlpha);
  Serial.println("-----------------------");
  
  if (meanOfDelta > 500000 && meanOfDelta < 700000) {
    internalState = HAPPY;
  }
  else if (meanOfHighBeta < 10000)  {
    internalState = RELAXED;
  }
  else if (meanOfLowGamma > 9000 && meanOfLowGamma < 12000)  {
    internalState = NONE;
  }
  else if (meanOfLowAlpha > 10000 && meanOfLowAlpha < 17000)  {
    internalState = ANXIOUS;
  }
  
  tasteTheRainbow(internalState);
  
  //Set the mean back to 0!
  meanOfDelta = 0;
  contentMean = 0;
  meanOfHighBeta = 0;
  dayDreamMean = 0;
  meanOfLowGamma = 0;
  focusedMean = 0;
  meanOfLowAlpha = 0;
  annoyedMean = 0;
  meanCounter = 0;  
}

