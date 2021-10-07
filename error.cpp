#include <iostream>

#include "error.h"

using namespace std;

void set_error(int err_code, string code_line, size_t instruction_num)
{
    switch (err_code) {
    case SYNTAX_ERROR:
        cout << "Syntax error in " << instruction_num + 1 << " instruction..." << endl;
        cout << "--> " << code_line << endl;
        exit(err_code);
        break;
    case UNKNOWN_OPERATION:
        cout << "Unknown operation in " << instruction_num + 1 << " instruction..." << endl;
        cout << "--> " << code_line << endl;
        exit(err_code);
        break;
    case INVALID_INPUT:
        cout << "Invalid value input in " << instruction_num + 1 << " instruction..." << endl;
        cout << "--> " << code_line << endl;
        exit(err_code);
        break;
    case INVALID_BASE:
        cout << "Invalid base in " << instruction_num + 1 << " instruction..." << endl;
        cout << "--> " << code_line << endl;
        exit(err_code);
        break;
    case DIVISION_BY_ZERO:
        cout << "Division by zero in " << instruction_num + 1 << " instruction..." << endl;
        cout << "--> " << code_line << endl;
        exit(err_code);
        break;
    case ERROR_SUCCESS:
        break;
    default:
        break;
    }
}
