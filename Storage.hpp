//
//  Storage.hpp
//  ECEDatabase
//
//  Created by rick gessner on 4/1/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef Storage_hpp
#define Storage_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <queue>
#include "Keywords.hpp"

namespace SF {
  
  static const int kBlockSize   = 768; //completely arbitary...
  
  //simple block header...
  struct BlockHeader {
    
    BlockHeader() : type('D'), dirty(false), id(0) {}
    
    BlockHeader(char aType, uint32_t anId) : type(aType), dirty(false), id(anId) {}
    
    BlockHeader(const BlockHeader &aCopy) {
      type=aCopy.type;
      dirty=aCopy.dirty;
      id=aCopy.id;
    }
    
    char      type;   //block type {[F]ree, [M]aster(singleton), [S]chema, [R]ecord}
    bool      dirty;  //currently unused...
    uint16_t  count;  //generic usage...
    uint32_t  id;     //id in most block; 1st free block for master...
  };
  
  struct EntityDef {
    uint32_t  hashId;
    uint32_t  blockId;
  };
  
  struct AttributeDef {
    char    name[17];  //len=16, and a null-terminator...
    char    type; //[B]ool, [C]har, [D]ate, [F]loat, [T]able, [V]archar...
    uint8_t length;
    uint8_t extra; //bits to represent other features...
  };
  
  //----- represents a single block in the storage file... -----------------
  
  struct Block {
    
    Block(char aType='D', uint32_t id=0) : header(aType, id) {}
    
    Block(BlockHeader &aHeader) : header(aHeader), data() {}
    
    //we use attributes[0] as table name...
    BlockHeader   header;
    union {
      EntityDef     schemas[(kBlockSize-sizeof(BlockHeader)/sizeof(EntityDef))]; //list of 95 tables...
      AttributeDef  attributes[(kBlockSize-sizeof(BlockHeader)/sizeof(AttributeDef))]; //schema fields...
      char          data[kBlockSize-sizeof(BlockHeader)];
    };
  };
  
  //------ actual i/o object...
  
  class Storage {
  protected:
    Block         master;
    std::fstream  stream;
    
    bool          isReady();
    uint32_t      getFreeBlock();
    uint32_t      getTotalBlockCount();
    uint32_t      getAutoIncrement();
    
    uint32_t      seekBlock(int aBlockNumber, bool aWrite=false);
    StatusResult  readBlock(int aBlockNumber, Block &aBlock, std::size_t aBlockSize=kBlockSize);
    StatusResult  writeBlock(int aBlockNumber, Block &aBlock);
    
    Storage(const Storage &aCopy); //prevent access...
    
  public:
    
    Storage(const std::string aName);
    
    
    ~Storage();
    
    StatusResult    makeEmpty(const std::string aName);
    
    StatusResult    addSchema(const std::string &aName, Block &aBlock);

    static uint32_t hashString(const char* aString);
    
    friend class Database;
    
  };
  
}

#endif /* Storage_hpp */
