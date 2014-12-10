#ifndef RAINBOWOUTPUT_H
#define RAINBOWOUTPUT_H

enum InternalState {
  NONE, ANXIOUS, HAPPY, RELAXED, DROWSY, INTERNAL_STATE_COUNT
};

const int GREEN_LED_PIN = 11;
const int RED_LED_PIN   = 10;
const int BLUE_LED_PIN  =  9;


void tasteTheRainbow(InternalState state);

#endif

