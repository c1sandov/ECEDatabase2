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

namespace SF {
  
  class Database {
    
    std::string   name;
    Storage       storage;
    
    StatusResult createTable(Tokenizer &aTokenizer);
    int describeTable(std::string aUserCommand);

  public:
    
    Database(const std::string aPath);
    
    Database(const Database &aDatabase);

    ~Database();
        
    std::string& getName() {return name;}
    
    int initializeStorage();
    
    StatusResult processSQL(std::string aSQLString);

  };
  
}

#endif /* Database_hpp */
