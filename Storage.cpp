//
//  Storage.cpp
//  ECEDatabase
//
//  Created by rick gessner on 4/1/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include "Storage.hpp"
#include <iostream>

namespace SF {
  
  const int gMultiplier = 37;
  
  uint32_t Storage::hashString(const char *str) {
    uint32_t h{0};
    unsigned char *p;
    for (p = (unsigned char*)str; *p != '\0'; p++)
      h = gMultiplier * h + *p;
    return h;
  }
  
  Storage::Storage(const std::string aName) : master('M',0) {
    char thePath[128];
    sprintf(thePath,"/tmp/%s.%s",aName.c_str(),"db");
    stream.open (thePath, std::fstream::binary | std::fstream::in | std::fstream::out);
    if(isReady()) {
      std::cout << "open error";
    }
  }
  
  Storage::Storage(const Storage &aCopy) {
  }
  
  Storage::~Storage() {
    if(master.header.dirty) {
      //save the master record...
      writeBlock(0,master);
    }
    stream.close();
  }
  
  StatusResult Storage::makeEmpty(const std::string aName) {
    if (stream.fail()) {
      //file didn't exist, so let's make it...
      
      char thePath[128];
      sprintf(thePath,"/tmp/%s.%s",aName.c_str(),"db");
      
      stream.clear(); // Clear Flag
      stream.open(thePath, std::fstream::in | std::fstream::out | std::fstream::trunc); // Create File
      stream.close();
      stream.open(thePath, std::fstream::binary | std::fstream::in | std::fstream::out); // Reopen for editing
    }
    
    master.header.count=0; //init for new db...
    memset(master.data,0,sizeof(master.data));
    return writeBlock(0, master);
  }
  
  bool Storage::isReady() {
    return stream.is_open();
  }
  
  uint32_t Storage::getAutoIncrement() {
    return ++master.header.id;
  }
  
  uint32_t Storage::getTotalBlockCount() {
    seekBlock(0);
    std::streampos theStart = stream.tellg();
    stream.seekg(0, std::fstream::end);
    return (uint32_t)((stream.tellg() - theStart)/kBlockSize);
  }
  
  //scan archive for free blocks, and store them here. If you need more use block number for appended blocks...
  uint32_t Storage::getFreeBlock() {
    if(master.header.id) {
      //we have a free block...
    }
    //otherwise append...
    return getTotalBlockCount();
  }
  
  uint32_t Storage::seekBlock(int aBlockNumber, bool aWrite) {
    int thePos = aBlockNumber * kBlockSize;
    if(aWrite) {
      stream.seekp(thePos);
      thePos = (int)stream.tellp();
      return thePos;
    }
    stream.seekg(thePos);
    return (thePos==(int)stream.tellg()) ? thePos : 0;
  }
  
  StatusResult Storage::readBlock(int aBlockNumber, Block &aBlock, std::size_t aBlockSize) {
    int thePos=seekBlock(aBlockNumber);
    if(thePos==(aBlockNumber*kBlockSize)) {
      stream.read ((char*)&aBlock.header, aBlockSize);
      return StatusResult{true};
    }
    return StatusResult{false,gReadError};
  }
  
  StatusResult Storage::writeBlock(int aBlockNumber, Block &aBlock) {
    std::cout<<"write-block " << aBlockNumber << std::endl;
    master.header.dirty=true;
    uint32_t thePos=seekBlock(aBlockNumber,true);
    if(thePos==(aBlockNumber*kBlockSize)) {
      stream.write ((char*)&aBlock.header, kBlockSize);
      int theNewPos = (int)stream.tellp();
      if(thePos==theNewPos) return StatusResult{false, gWriteError};
    }
    return StatusResult{true};
  }
  
  StatusResult Storage::addEntity(const std::string &aName, uint32_t aPos) {
    master.header.count++;
    master.entities[master.header.count].hashId=Storage::hashString(aName.c_str());
    master.entities[master.header.count].blockId=aPos;
    master.header.dirty=true;
    return StatusResult{true};
  }
  
}

