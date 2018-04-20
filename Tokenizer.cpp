//
//  Tokenizer.cpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include "Tokenizer.hpp"
#include <map>
#include <iostream>
#include <algorithm>

namespace SF {
  
  //const int maxlen = 2000;
  
  //if these numbers change, fix constants in header file...
  std::map<std::string, Keywords> gDictionary = {
    std::make_pair("add", Keywords::add_kw),
    std::make_pair("all", Keywords::all_kw),
    std::make_pair("alter", Keywords::alter_kw),
    std::make_pair("and", Keywords::and_kw),
    std::make_pair("between", Keywords::between_kw),
    std::make_pair("by", Keywords::by_kw),
    std::make_pair("char", Keywords::char_kw),
    std::make_pair("column", Keywords::column_kw),
    std::make_pair("create", Keywords::create_kw),
    std::make_pair("database", Keywords::database_kw),
    std::make_pair("databases", Keywords::databases_kw),
    std::make_pair("datetime", Keywords::datetime_kw),
    std::make_pair("decimal", Keywords::decimal_kw),
    std::make_pair("delete", Keywords::delete_kw),
    std::make_pair("distinct", Keywords::distinct_kw),
    std::make_pair("double", Keywords::double_kw),
    std::make_pair("drop", Keywords::drop_kw),
    std::make_pair("float", Keywords::float_kw),
    std::make_pair("foreign", Keywords::foreign_kw),
    std::make_pair("from", Keywords::from_kw),
    std::make_pair("in", Keywords::int_kw),
    std::make_pair("insert", Keywords::insert_kw),
    std::make_pair("int", Keywords::int_kw),
    std::make_pair("into", Keywords::into_kw),
    std::make_pair("key", Keywords::key_kw),
    std::make_pair("not", Keywords::not_kw),
    std::make_pair("null", Keywords::null_kw),
    std::make_pair("or", Keywords::or_kw),
    std::make_pair("primary", Keywords::primary_kw),
    std::make_pair("references", Keywords::references_kw),
    std::make_pair("select", Keywords::select_kw),
    std::make_pair("set", Keywords::set_kw),
    std::make_pair("show", Keywords::show_kw),
    std::make_pair("table", Keywords::table_kw),
    std::make_pair("unique", Keywords::unique_kw),
    std::make_pair("update", Keywords::update_kw),
    std::make_pair("use", Keywords::use_kw),
    std::make_pair("values", Keywords::values_kw),
    std::make_pair("varchar", Keywords::varchar_kw),
    std::make_pair("where", Keywords::where_kw)
  };
  
  //a list of known functions...
  std::map<std::string,int> gFunctions = {
    std::make_pair("avg", 10),
    std::make_pair("count", 20),
    std::make_pair("max", 30),
    std::make_pair("min", 40)
  };
  
  const char left_paren = '(';
  const char right_paren = ')';
  const char comma = ',';
  const char star = '*';
  const char gt = '>';
  const char lt = '<';
  
//  const char delim[] = {' ', '\t', '\n', '\r', '\0'};
//  const char operators[] = {'<','>','.','\0'};
//  const char semi_colon = ';';
//  const char plus_sign = '+';
//  const char minus_sign = '-';
//  const char slash = '/';
//  const char equal_sign = '=';
  
  //-----------------------------------------------------
  
  Tokenizer::Tokenizer(std::string anInput) : input(anInput)  {
  }
  
  Tokenizer::Tokenizer(const Tokenizer &aCopy) {
    
  }
  
  std::string Tokenizer::readWhile(std::string &aValidSet, bool addTerminal) {
    char theChar=input.peek();
    const char *theValidChars=aValidSet.c_str();
    std::string theResult;
    
    while(EOF!=theChar) {
      const char* thePos = strchr(theValidChars,theChar);
      if(!thePos) {
        if(addTerminal) {
          theResult+=input.get();
          break;
        }
      }
      theResult+=input.get();
      theChar=input.peek();
    }
    return theResult;
  }
  
  std::string Tokenizer::readUntil(std::string  &aTerminalSet, bool addTerminal){
    char theChar=input.peek();
    const char *theTerminals=aTerminalSet.c_str();
    std::string theResult;
    
    while(EOF!=theChar) {
      if(const char* thePos = strchr(theTerminals,theChar)) {
        if(addTerminal) theResult+=input.get();
        break;
      }
      else theResult+=input.get();
      theChar=input.peek();
    }
    return theResult;
  }
  
  
  std::string Tokenizer::readUntil(char aTerminalChar, bool addTerminal) {
    char theChar=input.peek();
    std::string theResult;
    
    while(EOF!=theChar) {
      if(theChar==aTerminalChar) {
        if(addTerminal) theResult+=input.get();
        break;
      }
      else theResult+=input.get();
      theChar=input.peek();
    }
    return theResult;
  }
  
  //we know first char is alpha...
  std::string Tokenizer::readIdentifier() {
    char theChar=input.peek();
    std::string theResult("");
    
    while(EOF!=theChar) {
      if(isalnum(theChar) || '_'==theChar) {
        theResult+=input.get();
        theChar=input.peek();
      }
      else break;
    }
    return theResult;
  }
  
  //we know first char is alpha...
  char Tokenizer::skipSpaces() {
    char theChar=input.peek();
    
    while(EOF!=theChar) {
      if(strchr(" \t\b\r\n",theChar)) {
        input.get();
      }
      else break;
      theChar=input.peek();
    }
    return input.peek();
  }
  
  bool is_punctuation(char aChar) {
    switch(aChar) {
      case left_paren:
      case right_paren :
      case comma:
        return true;
    }
    return false;
  }
  
  bool is_operator(char aChar) {
    switch(aChar) {
      case star:
      case gt :
      case lt: return true;
    }
    return false;
  }
  
  int Tokenizer::getFunctionId(const std::string anIdentifier) {
    auto theIter = gFunctions.find(anIdentifier);
    if (theIter != gFunctions.end()) {
      return theIter->second;
    }
    return 0;
  }
  
  Keywords Tokenizer::getKeywordId(const std::string aKeyword) {
    auto theIter = gDictionary.find(aKeyword);
    if (theIter != gDictionary.end()) {
      return theIter->second;
    }
    return Keywords::unknown_kw;
  }
  
  Token Tokenizer::tokenAt(int anOffset) {
    if(anOffset>=0 && anOffset<tokens.size()) {
      return tokens[anOffset];
    }
    return Token(TokenType::string, "?");
  }
  
  //run on input provided in constructor; produce vector of tokens...
  StatusResult Tokenizer::tokenize() {
    
    std::string numbers("-0123456789");
    StatusResult theResult;
    char  theChar = input.peek();
    
    while(EOF!=theChar) {
      if(is_punctuation(theChar)) {
        std::string temp;
        TokenType theType = TokenType::unknown;
        temp.push_back(input.get());
        switch(theChar) {
          case ',' : theType=TokenType::comma; break;
          case left_paren : theType=TokenType::lparen; break;
          case right_paren : theType=TokenType::rparen; break;
        }
        tokens.push_back(Token(theType,temp));
      }
      else if(is_operator(theChar)) {
        std::string temp;
        temp.push_back(input.get());
        tokens.push_back(Token(TokenType::operators,temp));
      }
      else if(isdigit(theChar)) {
        std::string theString=readWhile(numbers);
        tokens.push_back(Token(TokenType::number,theString));
      }
      else if(isalpha(theChar)) {
        std::string theString=readIdentifier();
        std::string temp(theString);
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        
        Keywords theKeyword = getKeywordId(temp);
        if(Keywords::unknown_kw!=theKeyword) {
          tokens.push_back(Token(TokenType::keyword, temp, theKeyword));
        }
        else if(getFunctionId(temp)) {
          tokens.push_back(Token(TokenType::function,temp));
        }
        else {
          tokens.push_back(Token(TokenType::identifier,theString));
        }
      }
      theChar=skipSpaces();
    }
    return theResult;
  }
  
  void Tokenizer::dump() {
    for (auto &theToken : tokens) {
      std::cout << "type ";
      switch(theToken.type) {
        case TokenType::comma:
        case TokenType::lparen:
        case TokenType::rparen:
        case TokenType::slash:
          std::cout << "punct " << theToken.data << std::endl;
          break;
          
        case TokenType::operators:
        case TokenType::star:
        case TokenType::equal:
        case TokenType::plus:
        case TokenType::minus:
          std::cout << "operator " << theToken.data << std::endl;
          break;
          
        case TokenType::number:
          std::cout << "number " << theToken.data << std::endl;
          break;
          
        case TokenType::string:
          std::cout << "string " << theToken.data << std::endl;
          break;
          
        case TokenType::identifier:
          std::cout << "identifier " << theToken.data << std::endl;
          break;
          
        case TokenType::keyword:
          std::cout << "keyword " << theToken.data << std::endl;
          break;
          
        default:
          break;
      }
    }
    
  }
  
}
