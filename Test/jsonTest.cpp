#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif


using namespace std;
using json = nlohmann::json;

int main(){
   
    // std::ifstream file("./resourse/TestJson/task.json");
    #ifdef _WIN32
     SetConsoleOutputCP(CP_UTF8); // 条件编译,设置控制台输出为UTF-8
     SetConsoleCP(CP_UTF8); // 设置控制台输入为UTF-8
    // std::locale::global(std::locale(".UTF8"));
    #endif
    
        std::cout << "---读取json文件---" << std::endl;
        std::cout << "--hello world-----" << std::endl;

        std::ifstream file("./resource/TestJson/task.json");
        std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        json j = json::parse(str);
        // std::cout << j[1] << std::endl;
        for(auto& [key, value] : j.items()){
             cout << "任务名称: " << key << endl;
            // 现在你可以通过 key 来访问对应的值
            cout << "任务内容: " << value << endl;
        }
        if (!file.is_open()) {
            cerr << "无法打开文件: ./resourse/task.json" << endl;
            return -1;
        }
        
    
    return 0;
}