#include "token.h"

int get_token_type(string token)
{
    int token_type = UNKNOWN_TOKEN;
    regex pattern_identifier("[a-zA-Z_][a-zA-Z0-9_]{0,31}");
    regex pattern_value("[-]{0,1}[0-9]+");
    if (regex_match(token, pattern_identifier))
    {
        token_type = IDENTIFIER;
    }
    else if (regex_match(token, pattern_value))
    {
        token_type = VALUE;
    }
    else
    {
        token_type = UNKNOWN_TOKEN;
    }
    return token_type;
}

int get_token_struct_0(const string code_line,
                       token_struct_t &token_struct,
                       map<string, string> &map_replace,
                       map<string, unsigned char> &opcode)
{
    string equality_sign = get_equality_sign(map_replace);
    regex pattern_binary(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                         string(")[\\s]*([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*;"));
    regex pattern_input_base(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                             string(")[\\s]*([[:graph:]]+)[\\s]*\\([\\s]*([0-9]+)[\\s]*\\)[\\s]*;"));
    regex pattern_input(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                        string(")[\\s]*([[:graph:]]+)[\\s]*\\([\\s]*\\)[\\s]*;"));
    regex pattern_output_base("([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([0-9]+)[\\s]*\\)[\\s]*;");
    regex pattern_output("([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*;");
    smatch token_match;
    if (regex_match(code_line, token_match, pattern_binary))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.operand_1 = token_match.str(4);
        token_struct.operand_2 = token_match.str(5);
    }
    else if (regex_match(code_line, token_match, pattern_input_base))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.base = stoi(token_match.str(4));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_input))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.base = 10;
    }
    else if (regex_match(code_line, token_match, pattern_output_base))
    {
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.operand_1 = token_match.str(2);
        token_struct.base = stoi(token_match.str(3));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_output))
    {
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.operand_1 = token_match.str(2);
        token_struct.base = 10;
    }
    else
    {
        return SYNTAX_ERROR;
    }
    if (token_struct.operation == 0)
    {
        return UNKNOWN_OPERATION;
    }
    return ERROR_SUCCESS;
}

int get_token_struct_1(const string code_line,
                       token_struct_t &token_struct,
                       map<string, string> &map_replace,
                       map<string, unsigned char> &opcode)
{
    string equality_sign = get_equality_sign(map_replace);
    regex pattern_binary(string("([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*(") +
                         equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input_base(string("([[:graph:]]+)[\\s]*\\([\\s]*([0-9]+)[\\s]*\\)[\\s]*(") +
                             equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input(string("([[:graph:]]+)[\\s]*\\([\\s]*\\)[\\s]*(") +
                        equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_output_base("([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([0-9]+)[\\s]*\\)[\\s]*;");
    regex pattern_output("([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*;");
    smatch token_match;
    if (regex_match(code_line, token_match, pattern_binary))
    {
        token_struct.result = token_match.str(5);
        token_struct.equ = map_replace[token_match.str(4)];
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.operand_1 = token_match.str(2);
        token_struct.operand_2 = token_match.str(3);
    }
    else if (regex_match(code_line, token_match, pattern_input_base))
    {
        token_struct.result = token_match.str(4);
        token_struct.equ = map_replace[token_match.str(3)];
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.base = stoi(token_match.str(2));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_input))
    {
        token_struct.result = token_match.str(3);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.base = 10;
    }
    else if (regex_match(code_line, token_match, pattern_output_base))
    {
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.operand_1 = token_match.str(2);
        token_struct.base = stoi(token_match.str(3));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_output))
    {
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.operand_1 = token_match.str(2);
        token_struct.base = 10;
    }
    else
    {
        return SYNTAX_ERROR;
    }
    if (token_struct.operation == 0)
    {
        return UNKNOWN_OPERATION;
    }
    return ERROR_SUCCESS;
}

int get_token_struct_2(const string code_line,
                       token_struct_t &token_struct,
                       map<string, string> &map_replace,
                       map<string, unsigned char> &opcode)
{
    string equality_sign = get_equality_sign(map_replace);
    regex pattern_binary(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                         string(")[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;"));
    regex pattern_input_base(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                             string(")[\\s]*\\([\\s]*([0-9]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;"));
    regex pattern_input(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                        string(")[\\s]*\\([\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;"));
    regex pattern_output_base("\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([0-9]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;");
    regex pattern_output("\\([\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;");
    smatch token_match;
    if (regex_match(code_line, token_match, pattern_binary))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(5)]];
        token_struct.operand_1 = token_match.str(3);
        token_struct.operand_2 = token_match.str(4);
    }
    else if (regex_match(code_line, token_match, pattern_input_base))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(4)]];
        token_struct.base = stoi(token_match.str(3));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_input))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.base = 10;
    }
    else if (regex_match(code_line, token_match, pattern_output_base))
    {
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.base = stoi(token_match.str(2));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_output))
    {
        token_struct.operation = opcode[map_replace[token_match.str(2)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.base = 10;
    }
    else
    {
        return SYNTAX_ERROR;
    }
    if (token_struct.operation == 0)
    {
        return UNKNOWN_OPERATION;
    }
    return ERROR_SUCCESS;
}

int get_token_struct_3(const string code_line,
                       token_struct_t &token_struct,
                       map<string, string> &map_replace,
                       map<string, unsigned char> &opcode)
{
    string equality_sign = get_equality_sign(map_replace);
    regex pattern_binary(string("\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*(") +
                         equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input_base(string("\\([\\s]*([0-9]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*(") +
                             equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input(string("\\([\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*(") +
                        equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_output_base("\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([0-9]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;");
    regex pattern_output("\\([\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;");
    smatch token_match;
    if (regex_match(code_line, token_match, pattern_binary))
    {
        token_struct.result = token_match.str(5);
        token_struct.equ = map_replace[token_match.str(4)];
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.operand_2 = token_match.str(2);
    }
    else if (regex_match(code_line, token_match, pattern_input_base))
    {
        token_struct.result = token_match.str(4);
        token_struct.equ = map_replace[token_match.str(3)];
        token_struct.operation = opcode[map_replace[token_match.str(2)]];
        token_struct.base = stoi(token_match.str(1));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_input))
    {
        token_struct.result = token_match.str(3);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.base = 10;
    }
    else if (regex_match(code_line, token_match, pattern_output_base))
    {
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.base = stoi(token_match.str(2));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_output))
    {
        token_struct.operation = opcode[map_replace[token_match.str(2)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.base = 10;
    }
    else
    {
        return SYNTAX_ERROR;
    }
    if (token_struct.operation == 0)
    {
        return UNKNOWN_OPERATION;
    }
    return ERROR_SUCCESS;
}

int get_token_struct_4(const string code_line,
                       token_struct_t &token_struct,
                       map<string, string> &map_replace,
                       map<string, unsigned char> &opcode)
{
    string equality_sign = get_equality_sign(map_replace);
    regex pattern_binary(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                         string(")[\\s]*([_0-9A-Za-z]+)[\\s]*[\\s]*([[:graph:]]+)[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input_base(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                             string(")[\\s]*([[:graph:]]+)[\\s]*\\([\\s]*([0-9]+)[\\s]*\\)[\\s]*;"));
    regex pattern_input(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                        string(")[\\s]*([[:graph:]]+)[\\s]*\\([\\s]*\\)[\\s]*;"));
    regex pattern_output_base("([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([0-9]+)[\\s]*\\)[\\s]*;");
    regex pattern_output("([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*;");
    smatch token_match;
    if (regex_match(code_line, token_match, pattern_binary))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(4)]];
        token_struct.operand_1 = token_match.str(3);
        token_struct.operand_2 = token_match.str(5);
    }
    else if (regex_match(code_line, token_match, pattern_input_base))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.base = stoi(token_match.str(4));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_input))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.base = 10;
    }
    else if (regex_match(code_line, token_match, pattern_output_base))
    {
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.operand_1 = token_match.str(2);
        token_struct.base = stoi(token_match.str(3));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_output))
    {
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.operand_1 = token_match.str(2);
        token_struct.base = 10;
    }
    else
    {
        return SYNTAX_ERROR;
    }
    if (token_struct.operation == 0)
    {
        return UNKNOWN_OPERATION;
    }
    return ERROR_SUCCESS;
}

int get_token_struct_5(const string code_line,
                       token_struct_t &token_struct,
                       map<string, string> &map_replace,
                       map<string, unsigned char> &opcode)
{
    string equality_sign = get_equality_sign(map_replace);
    regex pattern_binary(string("([_0-9A-Za-z]+)[\\s]*([[:graph:]]+)[\\s]*([_0-9A-Za-z]+)[\\s]*(") +
                         equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input_base(string("([[:graph:]]+)[\\s]*\\([\\s]*([0-9]+)[\\s]*\\)[\\s]*(") +
                             equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input(string("([[:graph:]]+)[\\s]*\\([\\s]*\\)[\\s]*(") +
                        equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_output_base("([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([0-9]+)[\\s]*\\)[\\s]*;");
    regex pattern_output("([[:graph:]]+)[\\s]*\\([\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*;");
    smatch token_match;
    if (regex_match(code_line, token_match, pattern_binary))
    {
        token_struct.result = token_match.str(5);
        token_struct.equ = map_replace[token_match.str(4)];
        token_struct.operation = opcode[map_replace[token_match.str(2)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.operand_2 = token_match.str(3);
    }
    else if (regex_match(code_line, token_match, pattern_input_base))
    {
        token_struct.result = token_match.str(4);
        token_struct.equ = map_replace[token_match.str(3)];
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.base = stoi(token_match.str(2));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_input))
    {
        token_struct.result = token_match.str(3);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.base = 10;
    }
    else if (regex_match(code_line, token_match, pattern_output_base))
    {
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.operand_1 = token_match.str(2);
        token_struct.base = stoi(token_match.str(3));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_output))
    {
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.operand_1 = token_match.str(2);
        token_struct.base = 10;
    }
    else
    {
        return SYNTAX_ERROR;
    }
    if (token_struct.operation == 0)
    {
        return UNKNOWN_OPERATION;
    }
    return ERROR_SUCCESS;
}

int get_token_struct_6(const string code_line,
                       token_struct_t &token_struct,
                       map<string, string> &map_replace,
                       map<string, unsigned char> &opcode)
{
    string equality_sign = get_equality_sign(map_replace);
    regex pattern_binary(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                         string(")[\\s]*([_0-9A-Za-z]+)[\\s]*[\\s]*([[:graph:]]+)[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input_base(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                             string(")[\\s]*\\([\\s]*([0-9]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;"));
    regex pattern_input(string("([_0-9A-Za-z]+)[\\s]*(") + equality_sign +
                        string(")[\\s]*\\([\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;"));
    regex pattern_output_base("\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([0-9]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;");
    regex pattern_output("\\([\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;");
    smatch token_match;
    if (regex_match(code_line, token_match, pattern_binary))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(4)]];
        token_struct.operand_1 = token_match.str(3);
        token_struct.operand_2 = token_match.str(5);
    }
    else if (regex_match(code_line, token_match, pattern_input_base))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(4)]];
        token_struct.base = stoi(token_match.str(3));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_input))
    {
        token_struct.result = token_match.str(1);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.base = 10;
    }
    else if (regex_match(code_line, token_match, pattern_output_base))
    {
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.base = stoi(token_match.str(2));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_output))
    {
        token_struct.operation = opcode[map_replace[token_match.str(2)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.base = 10;
    }
    else
    {
        return SYNTAX_ERROR;
    }
    if (token_struct.operation == 0)
    {
        return UNKNOWN_OPERATION;
    }
    return ERROR_SUCCESS;
}

int get_token_struct_7(const string code_line,
                       token_struct_t &token_struct,
                       map<string, string> &map_replace,
                       map<string, unsigned char> &opcode)
{
    string equality_sign = get_equality_sign(map_replace);
    regex pattern_binary(string("([_0-9A-Za-z]+)[\\s]*([[:graph:]]+)[\\s]*([_0-9A-Za-z]+)[\\s]*(") +
                         equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input_base(string("\\([\\s]*([0-9]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*(") +
                             equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_input(string("\\([\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*(") +
                        equality_sign + string(")[\\s]*([_0-9A-Za-z]+)[\\s]*;"));
    regex pattern_output_base("\\([\\s]*([_0-9A-Za-z]+)[\\s]*,[\\s]*([0-9]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;");
    regex pattern_output("\\([\\s]*([_0-9A-Za-z]+)[\\s]*\\)[\\s]*([[:graph:]]+)[\\s]*;");
    smatch token_match;
    if (regex_match(code_line, token_match, pattern_binary))
    {
        token_struct.result = token_match.str(5);
        token_struct.equ = map_replace[token_match.str(4)];
        token_struct.operation = opcode[map_replace[token_match.str(2)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.operand_2 = token_match.str(3);
    }
    else if (regex_match(code_line, token_match, pattern_input_base))
    {
        token_struct.result = token_match.str(4);
        token_struct.equ = map_replace[token_match.str(3)];
        token_struct.operation = opcode[map_replace[token_match.str(2)]];
        token_struct.base = stoi(token_match.str(1));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_input))
    {
        token_struct.result = token_match.str(3);
        token_struct.equ = map_replace[token_match.str(2)];
        token_struct.operation = opcode[map_replace[token_match.str(1)]];
        token_struct.base = 10;
    }
    else if (regex_match(code_line, token_match, pattern_output_base))
    {
        token_struct.operation = opcode[map_replace[token_match.str(3)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.base = stoi(token_match.str(2));
        if (token_struct.base < 2 || token_struct.base > 36)
        {
            return INVALID_BASE;
        }
    }
    else if (regex_match(code_line, token_match, pattern_output))
    {
        token_struct.operation = opcode[map_replace[token_match.str(2)]];
        token_struct.operand_1 = token_match.str(1);
        token_struct.base = 10;
    }
    else
    {
        return SYNTAX_ERROR;
    }
    if (token_struct.operation == 0)
    {
        return UNKNOWN_OPERATION;
    }
    return ERROR_SUCCESS;
}

string get_equality_sign(map<string, string> &map_replace)
{
    map<string, string>::iterator iter_replace;
    for (iter_replace = map_replace.begin(); iter_replace != map_replace.end(); iter_replace++)
    {
        if ((*iter_replace).second == "=")
        {
            break;
        }
    }
    return (*iter_replace).first;
}
