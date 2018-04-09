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
    stream.close();
  }

  int Storage::makeEmpty(const std::string aName) {
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
  
  int Storage::getTotalBlockCount() {
    seekBlock(0);
    std::streampos theStart = stream.tellg();
    stream.seekg(0, std::fstream::end);
    return (uint32_t)((stream.tellg() - theStart)/kBlockSize);
  }
  
  //scan archive for free blocks, and store them here. If you need more use block number for appended blocks...
  uint32_t Storage::getFreeBlock() {
    return 0;
  }
  
  int Storage::seekBlock(int aBlockNumber, bool aWrite) {
    int thePos = aBlockNumber * kBlockSize;
    if(aWrite) {
      stream.seekp(thePos);
      thePos = (int)stream.tellp();
      return thePos;
    }
    stream.seekg(thePos);
    thePos = (int)stream.tellg();
    return thePos;
  }
  
  int Storage::readBlock(int aBlockNumber, Block &aBlock, std::size_t aBlockSize) {
    int thePos=seekBlock(aBlockNumber);
    if(thePos==(aBlockNumber*kBlockSize)) {
      stream.read ((char*)&aBlock.header, aBlockSize);
      return (int)stream.gcount();
    }
    return 0;
  }
  
  int Storage::writeBlock(int aBlockNumber, Block &aBlock) {
    std::cout<<"write-block " << aBlockNumber << std::endl;
    if(aBlockNumber) master.header.dirty=true;
    int thePos=seekBlock(aBlockNumber,true);
    if(thePos==(aBlockNumber*kBlockSize)) {
      stream.write ((char*)&aBlock.header, kBlockSize);
      int theNewPos = (int)stream.tellp();
      return thePos<theNewPos ? kBlockSize : 0;
    }
    return 0;
  }
  
}

