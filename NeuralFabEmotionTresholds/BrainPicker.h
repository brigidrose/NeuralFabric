
enum ParseState {
  BEGIN, SYNC, PLENGTH, PAYLOAD, CHECKSUM
};

typedef void (*BrainyCallback)(Brainy &brain);

byte buffer[200];

int incomingByte;	// for incoming serial data

int bufferIndex;
int packetSize;

ParseState parseState;

Brainy brain(Serial);


void pickMyBrain(BrainyCallback callback);


