#ifndef EXECUTE_H
#define EXECUTE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <regex>
#include <map>
#include <cmath>
#include <algorithm>

#include "error.h"
#include "token.h"

enum {
    ADD = 1,
    MULT,
    SUB,
    POW,
    DIV,
    REM,
    XOR,
    INPUT,
    OUTPUT,
};
using namespace std;

int execute(const token_struct_t &token_struct,
             map<string, int> &value_array);
int get_value(string value_name,
              map<string, int> value_array);

#endif // EXECUTE_H
