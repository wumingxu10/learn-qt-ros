#include "common.h"
#include "myLog.h"
#include <string>

int main(int argc,char** argv)
{
    common common;
    string log_path = common.get_log_path();
    cout << log_path << endl;
    myLog *my_log = new myLog(log_path,"common");

    LOG(INFO)<<"hello world in common test";
    delete my_log;

    return 0;
}