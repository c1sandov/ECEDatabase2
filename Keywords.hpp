//
//  Keywords.hpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef Keywords_h
#define Keywords_h

const int gKeywordExpected=100;
const int gStatementExpected=200;
const int gNoDatabaseSpecified=300;
const int gUnknownDatabase=400;
const int gTableExists=500;
const int gInvalidAttribute=600;

const int gUnknownCommand = 3000;
const int gInvalidCommand = 3100;

const int gEOF=9999;

namespace SF {
  
  enum class Keywords {
    add_kw, all_kw, alter_kw, and_kw,
    between_kw, by_kw,
    char_kw, column_kw, create_kw,
    database_kw, databases_kw, datetime_kw, decimal_kw, delete_kw, distinct_kw, double_kw, drop_kw,
    float_kw, foreign_kw, from_kw,
    in_kw, insert_kw, int_kw, into_kw,
    key_kw,  not_kw,  null_kw, or_kw, primary_kw,
    references_kw, select_kw, set_kw, show_kw, table_kw,
    unknown_kw, unique_kw, update_kw, use_kw,
    values_kw, varchar_kw, where_kw,
  };
  
  struct StatusResult {
    bool handled;
    int  code;
    
    StatusResult(bool aHandled=true, int aCode=0) :
    handled(aHandled), code(aCode) {}
    
    operator bool() {return handled;}
  };
  
}
#endif /* Keywords_h */
