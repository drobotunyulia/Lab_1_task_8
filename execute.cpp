#include "execute.h"

int other_to_dec(string value, int base)
{
    bool is_negative = false;
    int finished_value = 0;
    if (value[0] == '-')
    {
        is_negative = true;
        value.erase(0, 1);
    }
    for (size_t i = 0; i < value.length(); i++)
    {
        finished_value = finished_value * base + (isdigit(value[i]) ? value[i] - '0' : value[i] - 'A' + 10);
    }
    if (is_negative)
    {
        finished_value = 0 - finished_value;
    }
    return finished_value;
}

string dec_to_other(int value, int base)
{
    bool is_negative = false;
    if (value < 0)
    {
        is_negative = true;
        value = abs(value);
    }
    string finished_value;
    int digit, counter = 0;
    if (value == 0)
    {
        finished_value.push_back('0');
    }
    while(value > 0)
    {
        digit = value % base;
        finished_value.push_back(digit > 9 ? digit - 10 + 'A' : digit + '0');
        value = value / base;
        counter++;
    }
    reverse(finished_value.begin(), finished_value.end());
    if (is_negative)
    {
        finished_value.insert(finished_value.begin(), 1, '-');
    }
    return finished_value;
}

bool test_base(string value, int base)
{
    for (size_t i = 0; i < value.length(); i++)
    {
        if (isdigit(value[i]) && value[i] - 47 > base)
        {
            return false;
        }
        if (isalpha(value[i]) && value[i] - 54 > base)
        {
            return false;
        }
    }
    return true;
}

int execute(const token_struct_t &token_struct,
             map<string, int> &value_array)
{
    regex pattern_value("[a-zA-Z0-9]+");
    string input_str;
    switch (token_struct.operation) {
    case ADD:
        if (get_token_type(token_struct.result) != IDENTIFIER ||
                get_token_type(token_struct.operand_1) == UNKNOWN_TOKEN ||
                get_token_type(token_struct.operand_2) == UNKNOWN_TOKEN)
        {
            return SYNTAX_ERROR;
        }
        value_array[token_struct.result] = get_value(token_struct.operand_1, value_array) + get_value(token_struct.operand_2,  value_array);
        break;
    case MULT:
        if (get_token_type(token_struct.result) != IDENTIFIER ||
                get_token_type(token_struct.operand_1) == UNKNOWN_TOKEN ||
                get_token_type(token_struct.operand_2) == UNKNOWN_TOKEN)
        {
            return SYNTAX_ERROR;
        }
        value_array[token_struct.result] = get_value(token_struct.operand_1, value_array) * get_value(token_struct.operand_2,  value_array);
        break;
    case SUB:
        if (get_token_type(token_struct.result) != IDENTIFIER ||
                get_token_type(token_struct.operand_1) == UNKNOWN_TOKEN ||
                get_token_type(token_struct.operand_2) == UNKNOWN_TOKEN)
        {
            return SYNTAX_ERROR;
        }
        value_array[token_struct.result] = get_value(token_struct.operand_1, value_array) - get_value(token_struct.operand_2,  value_array);
        break;
    case POW:
        if (get_token_type(token_struct.result) != IDENTIFIER ||
                get_token_type(token_struct.operand_1) == UNKNOWN_TOKEN ||
                get_token_type(token_struct.operand_2) == UNKNOWN_TOKEN)
        {
            return SYNTAX_ERROR;
        }
        value_array[token_struct.result] = pow(get_value(token_struct.operand_1, value_array), get_value(token_struct.operand_2,  value_array));
        break;
    case DIV:
        if (get_value(token_struct.operand_2,  value_array) == 0)
        {
            return DIVISION_BY_ZERO;
        }
        value_array[token_struct.result] = get_value(token_struct.operand_1, value_array) / get_value(token_struct.operand_2,  value_array);
        break;
    case REM:
        if (get_value(token_struct.operand_2,  value_array) == 0)
        {
            return DIVISION_BY_ZERO;
        }
        value_array[token_struct.result] = get_value(token_struct.operand_1, value_array) % get_value(token_struct.operand_2,  value_array);
        break;
    case XOR:
        value_array[token_struct.result] = get_value(token_struct.operand_1, value_array) ^ get_value(token_struct.operand_2,  value_array);
        break;
    case INPUT:
        if (get_token_type(token_struct.result) != IDENTIFIER)
        {
            return SYNTAX_ERROR;
        }
        cout << "Enter value in " << token_struct.base << " base: ";
        cin >> input_str;
        transform(input_str.begin(), input_str.end(), input_str.begin(), ::toupper);
        if (!regex_match(input_str, pattern_value))
        {
            return INVALID_INPUT;
        }
        value_array[token_struct.result] = other_to_dec(input_str, token_struct.base);
        break;
    case OUTPUT:
        if (get_token_type(token_struct.operand_1) == IDENTIFIER)
        {
            cout << "The value with base " << token_struct.base << " is: ";
            cout << dec_to_other(value_array[token_struct.operand_1], token_struct.base) << endl;
        }
        else
        {
            return SYNTAX_ERROR;
        }
        break;
    }
    return ERROR_SUCCESS;
}

int get_value(string value_name,
              map<string, int> value_array)
{
    if (get_token_type(value_name) == VALUE)
    {
        return stoi(value_name);
    }
    if (get_token_type(value_name) == IDENTIFIER)
    {
        return value_array[value_name];
    }
    return 0;
}
