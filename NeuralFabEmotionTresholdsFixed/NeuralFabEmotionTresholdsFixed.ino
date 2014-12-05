#include "Brainy.h"
#include "BrainPicker.h"
#include "RainbowOutput.h"
#include "BrainWaveStats.h"
#include <math.h>

#define SMOOTHING_FACTOR (8)

BrainWaveStats deltaStats(SMOOTHING_FACTOR);
BrainWaveStats highBetaStats(SMOOTHING_FACTOR);
BrainWaveStats lowGammaStats(SMOOTHING_FACTOR);
BrainWaveStats lowAlphaStats(SMOOTHING_FACTOR);

InternalState internalState;

float val = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;


void setup() {
  incomingByte = 0;
  bufferIndex = 0;
  packetSize = 0;
  parseState = BEGIN;

  Serial.begin(57600);	// opens serial port, sets data rate to 9600 bps

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  
  internalState = NONE;
  tasteTheRainbow(internalState);
}

void loop() {
  pickMyBrain(brainActivity);
}


void brainActivity(Brainy &brain) {
  deltaStats.update( brain.readDelta() );
  highBetaStats.update( brain.readHighBeta() );
  lowGammaStats.update( brain.readLowGamma() );
  lowAlphaStats.update( brain.readLowAlpha() );
    
  //First print the mean OF DELTA
  Serial.println("The mean of delta / content / green is......");
  Serial.println(deltaStats.smoothedValue());
  Serial.println("-----------------------");
  
  //Print the mean OF HIGH BETA
  Serial.println("The mean of High beta / day dream / white is......");
  Serial.println(highBetaStats.smoothedValue());
  Serial.println("-----------------------");
  
  //Print the mean OF HIGH BETA
  //notbeta
  Serial.println("Themean of Low gamma / focused / blue is......");
  Serial.println(lowGammaStats.smoothedValue());
  Serial.println("-----------------------");
  
  //Print the mean OF HIGH BETA
  //notbeta
  Serial.println("The mean of Low alpha / annoyed / red is......");
  Serial.println(lowAlphaStats.smoothedValue());
  Serial.println("-----------------------");
  
  if (!deltaStats.ready())
    return;
    
  if (deltaStats.smoothedValue() > 500000 && deltaStats.smoothedValue() < 700000) {
    internalState = HAPPY;
  }
  else if (highBetaStats.smoothedValue() < 10000)  {
    internalState = RELAXED;
  }
  else if ((lowGammaStats.smoothedValue() > 9000) && (lowGammaStats.smoothedValue() < 12000))  {
    internalState = NONE;
  }
  else if ((lowAlphaStats.smoothedValue() > 10000) && (lowAlphaStats.smoothedValue() < 17000))  {
    internalState = ANXIOUS;
  }
  
  tasteTheRainbow(internalState);  
}

