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
    
    char      type;  //block type {[F]ree, [M]aster (only1), [E]ntity, [R]ecord}
    bool      dirty; //currently unused...
    uint16_t  count;  //generic usage...
    uint32_t  id; //just id?
  };

  struct EntityDef {
    char      name[18];
    uint32_t  recordId;
  };
  
  struct AttributeDef {
    char    name[17];  //len=16, and a null-terminator...
    char    type; //[F]loat, [C]har, [B]ool, [D]ate, [V]archar...
    uint8_t length;
    uint8_t extra; //bits to represent other features...
  };

  //----- represents a single block in the storage file... -----------------
  
  struct Block {
    
    Block(char aType='D', uint32_t id=0) : header(aType, id) {}
    
    Block(BlockHeader &aHeader) : header(aHeader), data() {}
    
    BlockHeader   header;
    union {
      EntityDef     entities[(kBlockSize-sizeof(BlockHeader)/sizeof(EntityDef))]; //list of tables...
      AttributeDef  attributes[(kBlockSize-sizeof(BlockHeader)/sizeof(AttributeDef))]; //schema fields...
      char          data[kBlockSize-sizeof(BlockHeader)];
    };
  };
  
  //------ actual i/o object...
  
  class Storage {
  protected:
    Block         master;
    std::fstream  stream;
    
    int       seekBlock(int aBlockNumber, bool aWrite=false);
    int       readBlock(int aBlockNumber, Block &aBlock, std::size_t aBlockSize=kBlockSize);
    int       writeBlock(int aBlockNumber, Block &aBlock);
    uint32_t  getFreeBlock();
    int       getTotalBlockCount();
    uint32_t  getAutoIncrement();
    bool isReady();

  public:
    
    Storage(const std::string aName);
    
    Storage(const Storage &aCopy);
    
    ~Storage();

    int makeEmpty(const std::string aName);
        
  };
  
}

#endif /* Storage_hpp */
