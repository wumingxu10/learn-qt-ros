#pragma once
#define GLOG_USE_GLOG_EXPORT
#include <glog/logging.h>
#include <iostream>
#include <mutex>
#include <string>

using namespace std;

class myLog {

public:
    myLog(const string& log_path, const string& log_file_name);
    ~myLog();

private:
    string log_path_;
    string log_file_name_;
};