//
//  DBManager.cpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include "DBManager.hpp"
#include "Tokenizer.hpp"
#include "Database.hpp"

namespace SF {
  
  DBManager DBManager::manager;
  
  DBManager::DBManager(){
    active=nullptr;
  }
  
  DBManager::~DBManager() {
    releaseDB();
  }
  
  DBManager& DBManager::releaseDB() {
    if(active) {
      delete active;
      active=nullptr;
    }
    return *this;
  }
  
  Database* DBManager::findDatabase(const std::string aName) {
    return nullptr;
  }
  
  StatusResult DBManager::createDatabase(const std::string aName) {
    return StatusResult{false};
  }
  
  StatusResult DBManager::dropDatabase(const std::string aName) {
    //TBD...
    return StatusResult(true);
  }
  
  StatusResult DBManager::showDatabases() {
    
    //---------------------------------------------------------------
    //TBD: show properties of all known DBs...
    //---------------------------------------------------------------
    
    return 0;
  }
  
  StatusResult DBManager::useDatabase(const std::string aName) {
    if(Database *theDB=findDatabase(aName)) {
      active=theDB;
    }
    return StatusResult{false,gUnknownDatabase};
  }
  
  StatusResult DBManager::handleCommand(std::string &aUserInput, ICommandable *aNext) {
    
    Tokenizer theTokenizer(aUserInput);
    StatusResult theResult=theTokenizer.tokenize();
    
    if(theResult) {
      Token theToken = theTokenizer.tokenAt(0);
      Keywords theKW=theTokenizer.getKeywordId(theToken.data);
      
      Token theToken1 = theTokenizer.tokenAt(1);
      Keywords theType=theTokenizer.getKeywordId(theToken1.data);
      
      switch(theKW) {
        case Keywords::create_kw:
          
          if(Keywords::database_kw==theType) {
            Token theNameToken = theTokenizer.tokenAt(2);
            return createDatabase(theNameToken.data);
          }
          else if(Keywords::table_kw==theType) {
            if(active) {
              return active->handleCommand(aUserInput);
            }
            return StatusResult(false,gNoDatabaseSpecified);
          }
          
          break;
          
        case Keywords::drop_kw:
          {
            Token theNameToken = theTokenizer.tokenAt(2);
            theResult=dropDatabase(theNameToken.data);
          }
          break;
          
        case Keywords::show_kw:
          if(Keywords::database_kw==theType) {
            showDatabases();
          }
          else {
            if(active) {
              return active->handleCommand(aUserInput);
            }
            return StatusResult(false,gNoDatabaseSpecified);
          }
          break;
          
        case Keywords::use_kw:
        {
          Token theDBName = theTokenizer.tokenAt(2);
          return useDatabase(theDBName.data);
        }
          break;
          
        default:
          break;
      };
      
      if(aNext) {
        return aNext->handleCommand(aUserInput);
      }
      return theResult;
    }
    
    return StatusResult(false);
  }
  
  //-------------------------
  
  DBManager& DBManager::getManager() {return manager;}
  
}
