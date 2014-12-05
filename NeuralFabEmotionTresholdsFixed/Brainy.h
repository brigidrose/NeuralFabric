#ifndef Brainy_h
#define Brainy_h

#include "Arduino.h"

#define MAX_PACKET_LENGTH 32
#define EEG_POWER_BANDS 8

class Brainy {
    public:
        Brainy(Stream &_brainStream);
        
        void clearPacket();
        void clearEegPower();
        boolean parsePacket(uint8_t* packetData, uint8_t packetLength);
        boolean hasEEG();
        
        // String with most recent error.
        char* readErrors();

        // Returns comme-delimited string of all available brain data.
        // Sequence is as below.
        char* readCSV();

        // Individual pieces of brain data.
        uint8_t readSignalQuality();
        uint8_t readAttention();
        uint8_t readMeditation();
        uint32_t* readPowerArray();
        float readDeltaFloat();
        uint32_t readDelta();
        uint32_t readTheta();
        uint32_t readLowAlpha();
        uint32_t readHighAlpha();
        uint32_t readLowBeta();
        uint32_t readHighBeta();
        uint32_t readLowGamma();
        uint32_t readMidGamma();
        
    private:
        Stream* brainStream; 
        boolean inPacket;
        uint8_t latestByte;
        uint8_t lastByte;
        uint8_t packetIndex;
        uint8_t checksum;
        uint8_t checksumAccumulator;
        uint8_t eegPowerLength;
        boolean hasPower;
        
        void printPacket(uint8_t* packetData);
        void init();
        void printCSV(); // maybe should be public?      
        void printDebug();

        // With current hardware, at most we would have...
        // 3 x 3 char uint8_t
        // 8 x 10 char uint32_t
        // 10 x 1 char commas
        // 1 x 1 char 0 (string termination)
        // -------------------------
        // 100 characters       
        char csvBuffer[100];
        
        // Longest error is
        // 22 x 1 char uint8_ts
        // 1 x 1 char 0 (string termination)
        char latestError[23];       
        
        uint8_t signalQuality;
        uint8_t attention;
        uint8_t meditation;

        boolean freshPacket;
        
        union floatConversion_t {
          uint32_t fixedPoint;
          float floatingPoint;
        };
        
        // Lighter to just make this public, instead of using the getter?
        uint32_t eegPower[EEG_POWER_BANDS];
};

#endif
