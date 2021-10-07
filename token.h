#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>
#include <cstdint>

#include "error.h"

enum {
    IDENTIFIER,
    VALUE,
    OPERATION,
    UNKNOWN_TOKEN
};

using namespace std;

typedef struct {
  string result;
  string operand_1;
  string operand_2;
  unsigned char operation;
  string equ;
  size_t base;
} token_struct_t;



int get_token_type(string token);
string get_equality_sign(map<string, string> &map_replace);

int get_token_struct_0(const string code_line, token_struct_t &token_struct,
                                  map<string, string> &map_replace,
                                  map<string, unsigned char> &opcode);
int get_token_struct_1(const string code_line, token_struct_t &token_struct,
                                  map<string, string> &map_replace,
                                  map<string, unsigned char> &opcode);
int get_token_struct_2(const string code_line, token_struct_t &token_struct, map<string,
                                  string> &map_replace, map<string,
                                  unsigned char> &opcode);
int get_token_struct_3(const string code_line, token_struct_t &token_struct,
                                  map<string, string> &map_replace,
                                  map<string, unsigned char> &opcode);
int get_token_struct_4(const string code_line, token_struct_t &token_struct,
                                  map<string, string> &map_replace,
                                  map<string, unsigned char> &opcode);
int get_token_struct_5(const string code_line, token_struct_t &token_struct, map<string,
                                  string> &map_replace, map<string,
                                  unsigned char> &opcode);
int get_token_struct_6(const string code_line, token_struct_t &token_struct,
                                  map<string, string> &map_replace,
                                  map<string, unsigned char> &opcode);
int get_token_struct_7(const string code_line, token_struct_t &token_struct,
                                  map<string, string> &map_replace,
                                  map<string, unsigned char> &opcode);

#endif // TOKEN_H
