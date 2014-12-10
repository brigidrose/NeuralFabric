

void pickMyBrain(BrainyCallback callback) {
  if (!Serial.available())
    return;
    
  incomingByte = Serial.read();

  switch (parseState) {
    
    case BEGIN: {
      if (incomingByte == 0xAA)
        parseState = SYNC;
      break;
    }
      
    case SYNC: {
      if (incomingByte == 0xAA)
        parseState = PLENGTH;
      break;
    }
    
    case PLENGTH: {
      if (incomingByte < 170) {
        packetSize = incomingByte;
        parseState = PAYLOAD;
        bufferIndex = 0;
      }
      else if (incomingByte > 170)
        parseState = BEGIN;
      // else PLENGTH was a Sync byte, keep reading                
      break;
    }
      
    case PAYLOAD: {
      buffer[bufferIndex++] = incomingByte;
      if (bufferIndex == packetSize) {
        parseState = CHECKSUM;
      }
      break;
    }
    
    case CHECKSUM: {
      int i;
      byte checkSum = 0;
  
      for (i = 0; i < packetSize; i++) {
        checkSum += buffer[i];
      }
  
      checkSum = (255 - checkSum);
  
      if (checkSum == incomingByte) {
        if (brain.parsePacket(buffer, packetSize)) {
          if (brain.hasEEG()) {
            if (brain.readSignalQuality() == 0) {
            
              callback(brain);
            
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
}
