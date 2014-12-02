#include "Brainy.h"

enum ParseState {
  BEGIN, SYNC, PLENGTH, PAYLOAD, CHECKSUM
};

byte buffer[200];

int incomingByte;	// for incoming serial data

int bufferIndex;
int packetSize;
ParseState parseState;

//Four horsemen of the meanpocolpyse
float annoyedMean;
float contentMean;
float dayDreamMean;
float focusedMean;

//The count master daddy
int meanCounter;

Brainy brain(Serial);

long interval = 1000; 
long previousMillis = 0;

const int greenLEDPin = 11;    // LED connected to digital pin 9
const int redLEDPin = 10;     // LED connected to digital pin 10
const int blueLEDPin = 9;    // LED connected to digital pin 11


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

  Serial.begin(57600);	// opens serial port, sets data rate to 9600 bps
  //bluetooth.begin(57600);

  pinMode(greenLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);
  pinMode(blueLEDPin,OUTPUT);
}

void loop() {
  if(Serial.available())  // If the bluetooth sent any characters
  {
    incomingByte = Serial.read();

    switch (parseState) {
    case BEGIN:
      if (incomingByte == 0xAA)
        parseState = SYNC;
      break;  
    case SYNC:
      if (incomingByte == 0xAA)
        parseState = PLENGTH;
      break;
    case PLENGTH:
      if (incomingByte < 170) {
        packetSize = incomingByte;
        parseState = PAYLOAD;
        bufferIndex = 0;
      }
      else if (incomingByte > 170)
        parseState = BEGIN;
      // else PLENGTH was a Sync byte, keep reading                
      break;
    case PAYLOAD:                                    
      buffer[bufferIndex++] = incomingByte;
      if (bufferIndex == packetSize) {
        parseState = CHECKSUM;
      }
      break;
    case CHECKSUM:
      int i;
      byte checkSum = 0;

      for (i = 0; i < packetSize; i++) {
        checkSum += buffer[i];
      }

      checkSum = 255 - checkSum;

      if (checkSum == incomingByte) {
        //                if (buffer[0] != 0x80) {
        //                  for (i = 0; i < packetSize; i++) {
        //                    Serial.print(buffer[i], DEC);
        //                    Serial.print(" ");
        //                    //Serial.println(packetSize);
        //                  }
        //                  Serial.println();
        //                }
        if (brain.parsePacket(buffer, packetSize)) {
          if (brain.hasEEG()) {

            if(brain.readSignalQuality() == 0) {

              //add +1 to the meancounter!
              meanCounter++;

              //Serial.println(brain.readCSV());
              //Serial.println(brain.readDelta());

              //First, we have to detect when time is greater than 60,000
              unsigned long currentMillis = millis();

              //Capture and record the Delta values
              //Add every content value together
              float deltaValue = brain.readDelta();
              float highBetaValue = brain.readHighBeta();
              float lowGammaValue = brain.readLowGamma();
              float lowAlphaValue = brain.readLowAlpha();
              //Serial.println(deltaValue);
              //Serial.println(highBetaValue);

              dayDreamMean = dayDreamMean + highBetaValue;
              contentMean = contentMean + deltaValue;
              focusedMean = focusedMean + lowGammaValue;
              annoyedMean = annoyedMean + lowAlphaValue;

              ///////////A MINUTE IS UP //////////////////////////////
              if(currentMillis - previousMillis > interval) {
                previousMillis = currentMillis;

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

                //CONTENT
                if (meanOfDelta > 500000 && meanOfDelta < 700000) {
                  digitalWrite(greenLEDPin, HIGH);
                  digitalWrite(redLEDPin, LOW);
                  digitalWrite(blueLEDPin, LOW);
                }
                //Day Dream
                else if (meanOfHighBeta < 10000)  {
                  digitalWrite(blueLEDPin, HIGH);
                  digitalWrite(greenLEDPin, HIGH);
                  digitalWrite(redLEDPin, HIGH);
                }

                //Focused
                else if (meanOfLowGamma > 9000 && meanOfLowGamma < 12000)  {
                  digitalWrite(blueLEDPin, HIGH);
                  digitalWrite(greenLEDPin, LOW);
                }

                //Annoyed
                else if (meanOfLowAlpha > 10000 && meanOfLowAlpha < 17000)  {
                  digitalWrite(redLEDPin, HIGH);
                  digitalWrite(blueLEDPin, LOW);
                  digitalWrite(greenLEDPin, LOW);
                }


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
            }
            else {
              Serial.println("BAD SIGNAL - IGNORING THIS PACKET!");
            }

          }
        }
        else {
          Serial.println("Parse FAIL");
        }
      }


      parseState = BEGIN;
      break;
    }
  }

  //        if(Serial.available())  // If stuff was typed in the serial monitor
  //        {
  //          // Send any characters the Serial monitor prints to the bluetooth
  //          bluetooth.print((char)Serial.read());
  //        }
}
;

