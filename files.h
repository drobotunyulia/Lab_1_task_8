#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>
#include <cstdint>

#include "error.h"

#define LEFT 0x00
#define RIGHT 0x01
#define PREV 0x00
#define POST 0x02
#define MID 0x04

using namespace std;

vector<string> load_source_file(const string file_name);
char load_config_file(const string file_name,
                      map<string, string> &map_replace);
void save_config_file(const string file_name,
                      map<string, string> &map_replace,
                      char syntax_type);

#endif // FILES_H
