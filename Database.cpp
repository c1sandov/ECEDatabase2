//
//  Database.cpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include "Database.hpp"
#include "Parser.hpp"
#include "Tokenizer.hpp"

namespace SF {
  
  Database::Database(const std::string aName) : name(aName), storage(aName) {
  }
  
  Database::Database(const Database &aCopy) : name(aCopy.name), storage(aCopy.storage) {
  }
  
  Database::~Database() {
  }
  
  int Database::initializeStorage() {
    return storage.makeEmpty(name);
  }
  
  StatusResult Database::createTable(Tokenizer &aTokenizer) {
    return StatusResult{false};
  }
  
  int Database::describeTable(std::string aUserCommand) {
    
    //---------------------------------------------------------------
    //TBD: generate a string that represents table creation...
    //---------------------------------------------------------------
    
    return 0;
  }
  
  StatusResult Database::handleCommand(std::string &aUserInput,
                                       ICommandable *aNext) {
    StatusResult theResult;
    
    Tokenizer theTokenizer(aUserInput);
    theResult=theTokenizer.tokenize();
    
    if(theResult) {
      Token theToken = theTokenizer.tokenAt(0);
      Keywords theKW=theTokenizer.getKeywordId(theToken.data);
      switch(theKW) {
        case Keywords::create_kw: //create table...
          break;
          
        case Keywords::alter_kw:  //alter table...
          break;
          
        case Keywords::drop_kw:   //drop table...
          break;
          
        case Keywords::insert_kw:  //insert record(s)...
          break;
          
        case Keywords::update_kw:  //update record(s)...
          break;
          
        case Keywords::delete_kw:  //delete records(s)...
          break;
          
        case Keywords::select_kw:  //select records(s)...
          break;
          
        default:
          break;
      };
    }
    return theResult;
  }
  
}
