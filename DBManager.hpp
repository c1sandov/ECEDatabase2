//
//  DBManager.hpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef DBManager_hpp
#define DBManager_hpp

#include <stdio.h>
#include <string>
#include "CommandProcessor.hpp"

namespace SF {
  
  class Database;
  
  class DBManager : public ICommandable {
  protected:
  
    static DBManager manager;

    Database      *active;
  
    DBManager&  releaseDB();
    Database* findDatabase(std::string aName);
    
  public:
    
    DBManager();
    virtual ~DBManager();

    static DBManager& getManager();
    
      //db related commands...
    StatusResult useDatabase(std::string aName);
    StatusResult createDatabase(std::string aName);
    StatusResult dropDatabase(std::string aName);
    StatusResult showDatabases();

    virtual StatusResult  handleCommand(std::string &aUserInput, ICommandable *aNext);

  };
  
}

#endif /* DBManager_hpp */