#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <unistd.h>

using namespace std;

class common {

public:
    common();
    ~common();

    string get_log_path();
    string get_cur_path();
    void creat_multilevel_dir(const char* dir);

};