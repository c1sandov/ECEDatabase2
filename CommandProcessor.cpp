//
//  CommandProcessor.cpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

//
//  SFCommandProcessor.cpp
//  SFDatabase
//
//  KNOWN COMMANDS:
//    create   database |  table
//    delete * from ...
//    describe table
//    drop     database | table
//    help     output available commands on terminal...
//    insert   into ...
//    select * from
//    show     databases | tables
//    update   ...
//    use      database foo
//
//  Created by rick gessner on 3/28/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include <iostream>
#include <map>
#include "CommandProcessor.hpp"
#include "DBManager.hpp"

namespace SF {
  
  CommandProcessor::CommandProcessor(bool aRunning) : running(aRunning){}
  
  CommandProcessor::~CommandProcessor() {}
  
  size_t getUserInput(std::string &anInput) {
    getline(std::cin, anInput);
    return anInput.length();
  }
  
  StatusResult CommandProcessor::handleCommand(std::string &aUserInput, ICommandable *aNext) {
    std::string theKeyword=aUserInput.substr(0, aUserInput.find(" "));
    
    if("quit"==theKeyword) {
      running=false;
      return StatusResult();
    }
    if("version"==theKeyword || "ver"==theKeyword) {
      std::cout << "version 0.2" << std::endl;
      return StatusResult();
    }
    
    if(aNext) {
      return aNext->handleCommand(aUserInput,nullptr);
    }
    return StatusResult(false);
  }
  
  StatusResult CommandProcessor::run() {
    
    StatusResult theResult{};
    
    CommandProcessor theProcessor;
    DBManager theManager = DBManager::getManager();
    
    std::string theUserInput;
    theProcessor.running=true; 
    while(theProcessor.running && getUserInput(theUserInput)) {
      theResult = theManager.handleCommand(theUserInput,&theProcessor);
    }
    return theResult;
  }
  
}

