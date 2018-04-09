//
//  Tokenizer.hpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef Tokenizer_hpp
#define Tokenizer_hpp

#include <stdio.h>
#include "Token.hpp"
#include "Keywords.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace SF {
  
  class Tokenizer {
  protected:
    std::vector<Token>  tokens;
    std::istringstream    input;
    
    std::string readUntil(char aTerminal, bool addTerminal=false);
    
    std::string readUntil(std::string & aTermSet,bool addTerminal=false);
    
    std::string readWhile(std::string & anInputSet, bool addTerminal=false);
    
    std::string readIdentifier(); //starts with alpha, then alphanum...
    
    char skipSpaces();
    
    
  public:
    
    Tokenizer(std::string anInput);
    
    Tokenizer(const Tokenizer &aCopy);
    
    size_t size() {return tokens.size();}
    
    StatusResult tokenize();
    
    Token tokenAt(int anOffset);
    
    static  Keywords  getKeywordId(const std::string aKeyword);
    static  int       getFunctionId(const std::string anIdentifier);
    
    void dump();
    
  };
    
}

#endif /* Tokenizer_hpp */
