#ifndef ERROR_H
#define ERROR_H

#include "files.h"

enum {
    ERROR_SUCCESS = 0,
    SOURCE_FILE_ERROR = -1,
    CONFIG_FILE_ERROR = -2,
    SYNTAX_ERROR = -3,
    UNKNOWN_OPERATION = -4,
    COMMENT_ERROR = -5,
    INVALID_INPUT = -6,
    DIVISION_BY_ZERO = -7,
    INVALID_BASE = -8
};

using namespace std;

void set_error(int error_code, string code_line, size_t instruction_num);

#endif // ERROR_H
