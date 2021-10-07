#include "files.h"

string space_delete(string str)
{
    string result_str;
    regex pattern_space("(\\s)+");
    result_str = regex_replace(str, pattern_space, "$1");
    if (isblank(result_str[0]))
    {
        result_str.erase(0, 1);
    }
    if (*(result_str.end() - 1) == '\n')
    {
        result_str.erase(result_str.end() - 1, result_str.end());
    }
    return result_str;
}

vector<string> load_source_file(const string file_name)
{
    vector<string> source_text;
    string code_line;
    char input_byte;
    size_t bracket_count = 0;
    ifstream source_file(file_name, ios::binary);
    if (!source_file)
    {
        cout << "Source file open error..." << endl;
        exit(SOURCE_FILE_ERROR);
    }
    while (!source_file.eof())
    {
        source_file.get(input_byte);
        if (input_byte == '[')
        {
            bracket_count++;
        }
        if (input_byte == ']' && bracket_count > 0)
        {
            bracket_count--;
            source_file.get(input_byte);
        }
        if (input_byte == ']' && bracket_count == 0)
        {
            cout << "Invalid comment..." << endl;
            exit(COMMENT_ERROR);
        }
        if (bracket_count == 0 && input_byte != ']')
        {
            code_line.push_back(input_byte);
        }
        if (input_byte == '\n')
        {
            if (!code_line.empty() && code_line[0] != 10 && code_line[0] != 13)
            {
                source_text.push_back(space_delete(code_line));
            }
            code_line.clear();
        }
    }
    if (bracket_count != 0)
    {
        cout << "Invalid comment..." << endl;
        exit(COMMENT_ERROR);
    }
    source_file.close();
    return source_text;
}

char load_config_file(const string file_name, map<string, string> &map_replace)
{
    const regex pattern_replace("([[:graph:]]+)[[:blank:]]+([[:graph:]]+)[[:blank:]]*");
    smatch match_replace;
    char syntax_type = 0;
    vector<string> config_text;
    string config_line;
    ifstream config_file(file_name);
    if (!config_file)
    {
        cout << "Config file open error...";
        return syntax_type;
    }
    while (!config_file.eof())
    {
        getline(config_file, config_line);
        if (config_line[0] != '#')
        {
            config_text.push_back(config_line);
        }
    }
    config_file.close();
    for (size_t i = 0; i < config_text.size(); i++)
    {

        if (regex_match(config_text[i], match_replace, pattern_replace))
        {
            map_replace[match_replace.str(2)] = match_replace.str(1);
        }
        else
        {
            if (config_text[i] == "right=")
            {
                syntax_type = syntax_type | RIGHT;
            }
            else if (config_text[i] == "left=")
            {
                syntax_type = syntax_type | LEFT;
            }
            else if (config_text[i] == "op()")
            {
                syntax_type = syntax_type | PREV;
            }
            else if (config_text[i] == "()op")
            {
                syntax_type = syntax_type | POST;
            }
            else if (config_text[i] == "(op)()")
            {
                syntax_type = syntax_type | PREV | MID;
            }
            else if (config_text[i] == "()(op)")
            {
                syntax_type = syntax_type | POST | MID;
            }
        }
    }
    return syntax_type;
}

void save_config_file(const string file_name, map<string, string> &map_replace, char syntax_type)
{
    map<string, string>::iterator iter_replace;
    ofstream config_file(file_name);
    if (!config_file)
    {
        cout << "Config file open error...";
    }
    config_file << "#map replace:" << endl;
    for (iter_replace = map_replace.begin(); iter_replace != map_replace.end(); iter_replace++)
    {
        config_file << (*iter_replace).second << " " << (*iter_replace).first << endl;
    }
    config_file << "#syntax type:" << endl;
    if (syntax_type == 0)
    {
        config_file << "left=" << endl;
        config_file << "op()" << endl;
    }
    else if (syntax_type == 1)
    {
        config_file << "right=" << endl;
        config_file << "op()" << endl;
    }
    else if (syntax_type == 2)
    {
        config_file << "left=" << endl;
        config_file << "()op" << endl;
    }
    else if (syntax_type == 3)
    {
        config_file << "right=" << endl;
        config_file << "()op" << endl;
    }
    else if (syntax_type == 4)
    {
        config_file << "left=" << endl;
        config_file << "(op)()" << endl;
    }
    else if (syntax_type == 5)
    {
        config_file << "right=" << endl;
        config_file << "(op)()" << endl;
    }
    else if (syntax_type == 6)
    {
        config_file << "left=" << endl;
        config_file << "()(op)" << endl;
    }
    else if (syntax_type == 7)
    {
        config_file << "right=" << endl;
        config_file << "()(op)" << endl;
    }
    config_file.close();
}
