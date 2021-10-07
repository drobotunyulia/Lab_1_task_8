#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <regex>

#include "error.h"
#include "files.h"
#include "token.h"
#include "execute.h"

using namespace std;

const string default_config_file_name("interpreter.cfg");

bool is_key_in_map_replace(map<string, string> map_replace, string key)
{
    map<string, string>::iterator iter_replace;
    for (iter_replace = map_replace.begin(); iter_replace != map_replace.end(); iter_replace++)
    {
        if ((*iter_replace).second == key)
        {
            return true;
        }
    }
    return false;
}


int main(int argc, char *argv[])
{
    int err_code = ERROR_SUCCESS;
    token_struct_t token_struct;
    size_t instruction_num = 0;
    map<string, int> value_array;
    string config_file_name;
    map<string, unsigned char> opcode;
    opcode["add"] = ADD;
    opcode["mult"] = MULT;
    opcode["sub"] = SUB;
    opcode["pow"] = POW;
    opcode["div"] = DIV;
    opcode["rem"] = REM;
    opcode["xor"] = XOR;
    opcode["input"] = INPUT;
    opcode["output"] = OUTPUT;

    map<string, string> map_replace;

    if (argc < 3)
    {
        config_file_name = default_config_file_name;
    }
    else
    {
        config_file_name = string(argv[2]);
    }
    if (argc < 2)
    {
        cout << "The source file is not specified..." << endl;
        exit(SOURCE_FILE_ERROR);
    }
    char syntax_type = load_config_file(config_file_name, map_replace);
    vector<string> source_text = load_source_file(string(argv[1]));
    if (!is_key_in_map_replace(map_replace, "add"))
    {
        map_replace["add"] = "add";
    }
    if (!is_key_in_map_replace(map_replace, "mult"))
    {
        map_replace["mult"] = "mult";
    }
    if (!is_key_in_map_replace(map_replace, "sub"))
    {
        map_replace["sub"] = "sub";
    }
    if (!is_key_in_map_replace(map_replace, "pow"))
    {
        map_replace["pow"] = "pow";
    }
    if (!is_key_in_map_replace(map_replace, "div"))
    {
        map_replace["div"] = "div";
    }
    if (!is_key_in_map_replace(map_replace, "rem"))
    {
        map_replace["rem"] = "rem";
    }
    if (!is_key_in_map_replace(map_replace, "xor"))
    {
        map_replace["xor"] = "xor";
    }
    if (!is_key_in_map_replace(map_replace, "input"))
    {
        map_replace["input"] = "input";
    }
    if (!is_key_in_map_replace(map_replace, "output"))
    {
        map_replace["output"] = "output";
    }
    if (!is_key_in_map_replace(map_replace, "="))
    {
        map_replace["="] = "=";
    }
    for (size_t i = 0; i < source_text.size(); i++)
    {
        instruction_num = i;
        switch(syntax_type) {
        case 0:
            err_code = get_token_struct_0(source_text[i], token_struct, map_replace, opcode);
            set_error(err_code, source_text[i], instruction_num);
            err_code = execute(token_struct, value_array);
            set_error(err_code, source_text[i], instruction_num);
            break;
        case 1:
            err_code = get_token_struct_1(source_text[i], token_struct, map_replace, opcode);
            set_error(err_code, source_text[i], instruction_num);
            err_code = execute(token_struct, value_array);
            set_error(err_code, source_text[i], instruction_num);
            break;
        case 2:
            err_code = get_token_struct_2(source_text[i], token_struct, map_replace, opcode);
            set_error(err_code, source_text[i], instruction_num);
            err_code = execute(token_struct, value_array);
            set_error(err_code, source_text[i], instruction_num);
            break;
        case 3:
            err_code = get_token_struct_3(source_text[i], token_struct, map_replace, opcode);
            set_error(err_code, source_text[i], instruction_num);
            err_code = execute(token_struct, value_array);
            set_error(err_code, source_text[i], instruction_num);
            break;
        case 4:
            err_code = get_token_struct_4(source_text[i], token_struct, map_replace, opcode);
            set_error(err_code, source_text[i], instruction_num);
            err_code = execute(token_struct, value_array);
            set_error(err_code, source_text[i], instruction_num);
            break;
        case 5:
            err_code = get_token_struct_5(source_text[i], token_struct, map_replace, opcode);
            set_error(err_code, source_text[i], instruction_num);
            err_code = execute(token_struct, value_array);
            set_error(err_code, source_text[i], instruction_num);
            break;
        case 6:
            err_code = get_token_struct_6(source_text[i], token_struct, map_replace, opcode);
            set_error(err_code, source_text[i], instruction_num);
            err_code = execute(token_struct, value_array);
            set_error(err_code, source_text[i], instruction_num);
            break;
        case 7:
            err_code = get_token_struct_7(source_text[i], token_struct, map_replace, opcode);
            set_error(err_code, source_text[i], instruction_num);
            err_code = execute(token_struct, value_array);
            set_error(err_code, source_text[i], instruction_num);
            break;
        default:
            break;
        }
    }
    save_config_file(default_config_file_name, map_replace, syntax_type);
    return 0;
}
