//#include <SoftwareSerial.h>  

//int bluetoothTx = 0;  // TX-O pin of bluetooth mate, Arduino D2
//int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

//SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

enum ParseState {
  BEGIN, SYNC, PLENGTH, PAYLOAD, CHECKSUM
};

byte buffer[200];

int incomingByte;	// for incoming serial data

int bufferIndex;
int packetSize;
ParseState parseState;


void setup() {
        incomingByte = 0;
        bufferIndex = 0;
        packetSize = 0;
        parseState = BEGIN;
  
	Serial.begin(57600);	// opens serial port, sets data rate to 9600 bps
        //bluetooth.begin(57600);
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
              
//              if (checkSum == incomingByte) {
                if (buffer[0] != 0x80) {
                  for (i = 0; i < packetSize; i++) {
                    Serial.print(buffer[i], DEC);
                    Serial.print(" ");
                    //Serial.println(packetSize);
                  }
                  Serial.println();
                }
//              }
              else {
                Serial.println("Checksum FAIL");
                Serial.println(packetSize);
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


