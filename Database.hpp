//
//  Database.hpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp


#include <stdio.h>
#include <string>
#include <vector>
#include "Storage.hpp"
#include "Tokenizer.hpp"
#include "CommandProcessor.hpp"

namespace SF {
  
  class Database : public ICommandable {
    
    std::string   name;
    Storage       storage;
    
    StatusResult createTable(Tokenizer &aTokenizer);
    int describeTable(std::string aUserCommand);
    
  public:
    
    Database(const std::string aPath);
    
    Database(const Database &aDatabase);
    
    virtual ~Database();
    
    std::string& getName() {return name;}
    
    int initializeStorage();
    
    virtual StatusResult handleCommand(std::string &aUserInput, ICommandable *aNext=nullptr);
    
  };
  
}

#endif /* Database_hpp */
