
//
//  Parser.hpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include "Token.hpp"

namespace SF {
  
  const int kFunctionExpected = 100;
  const int kFromExpected = 200;
  const int kWhereExpected = 300;
  const int kTableNameExpected = 400;
  
  class Tokenizer;
  
  class Parser {
  protected:
    
    int  pos;
    
  public:
    
    Tokenizer &tokenizer;
    
    Parser(Tokenizer &aTokenizer);
    
    Parser(const Parser &aCopy);
    
    virtual ~Parser();
    
    bool  peekToken(Token &aToken, int anOffset=1); //peek ahead
    bool  getToken(Token &aToken); //get current
    bool  nextToken(Token &aToken); //move ptr ahead...
    
    bool  skipKeyword(Keywords aKeyword, Token &aToken);
    
    Keywords  getKeywordId(std::string aKeyword); //delegated to tokenizer...
    int       getFunctionId(std::string anIdentifier);
    
    virtual int parse();
    
  };


}

#endif /* Parser_hpp */
