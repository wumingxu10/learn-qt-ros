#include "common.h"


common::common()
{

}

common::~common()
{

}

string common::get_log_path()
{
    string cur_path = get_cur_path();
    int idx = cur_path.find_last_of('/');
    string log_Path = cur_path.substr(0,idx) + "/logs";
    if(access(log_Path.c_str(),0))
    {
        cout << "log path is not exist,creat it..."<< endl;
        creat_multilevel_dir(log_Path.c_str());
    }

    return log_Path;
}

string common::get_cur_path()
{
    char* current_path;
    current_path = getcwd(NULL,0);
    string str_cur_path(current_path,strlen(current_path));
    free(current_path);
    return str_cur_path;
}

void common::creat_multilevel_dir(const char* dir)
{
    char cmd[100]="mkdir -p ";
    strcat(cmd,dir);
    system(cmd);
}
