//
//  Parser.cpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//


#include <vector>
#include <stdio.h>
#include "Parser.hpp"
#include "Tokenizer.hpp"

namespace SF {
  
  Parser::Parser(Tokenizer &aTokenizer) : tokenizer(aTokenizer), pos(0) {}
  
  Parser::Parser(const Parser &aCopy) : tokenizer(aCopy.tokenizer), pos(aCopy.pos) {}
  
  Parser::~Parser() {}
  
  int Parser::getFunctionId(std::string anIdentifier) {
    return tokenizer.getFunctionId(anIdentifier);
  }
  
  Keywords Parser::getKeywordId(std::string aKeyword) {
    return Tokenizer::getKeywordId(aKeyword);
  }
  
  //peek ahead to next token
  bool Parser::peekToken(Token &aToken, int anOffset) {
    if(pos+anOffset<tokenizer.size()) {
      aToken=tokenizer.tokenAt(pos+anOffset);
      return true;
    }
    return false;
  }
  
  bool Parser::getToken(Token &aToken) {
    if(pos<tokenizer.size()) {
      aToken=tokenizer.tokenAt(pos);
      return true;
    }
    return false;
  }
  
  bool Parser::nextToken(Token &aToken) {
    pos++;
    return getToken(aToken);
  }
  
  bool Parser::skipKeyword(Keywords aKeyword, Token &aToken) {
    while(getToken(aToken)) {
      if (aKeyword==tokenizer.getKeywordId(aToken.data)) {
        nextToken(aToken);
        return true;
      }
      nextToken(aToken);
    }
    return false;
  }
  
  int Parser::parse() {
    return gEOF;
  }
  
}
