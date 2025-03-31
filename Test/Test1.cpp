#ifdef _WIN32                           //在windows下编译时
    #ifdef MAA_TEST_EXPORTS                     
        #define TEST_API __declspec(dllexport) //
    #else
        #define TEST_API __declspec(dllimport)
    #endif
#else
    #define TEST_API    // 非Windows下编译时
#endif

#include <fstream> 
#include <iostream>
#include <string>
#include <cstring> 
#include <nlohmann/json.hpp> 
#include <filesystem>

// 预编译部分
#ifdef _WIN32                           //在windows下编译时
    #include <windows.h>
#endif                 

extern "C"{
    class _Test1{

    };

    struct Test1
    {
        const char* name;
        int age;
    };
    
    TEST_API void Test1SetName(Test1* obj, const char* name){
            if(obj->name != nullptr) {
                free((void*)obj->name); 
            }
            obj->name = _strdup(name);
            std::cout << "set name to " << obj->name <<std::endl;
    };

    TEST_API void Test1SetAge(Test1* obj, int age){
        obj->age = age;
    };

    TEST_API const char* Test1GetName(Test1* obj){
        std::cout << "get name " << obj->name <<std::endl;
        return obj->name;
    };

    TEST_API int Test1GetAge(Test1* obj){
        return obj->age;
    };

    TEST_API void Test1Free(Test1* obj){
            free((void*)obj->name);
            obj->name = nullptr;
    };

    TEST_API void Test1ReadJosn(const char* filePath){
        nlohmann::json j;
        std::ifstream file(filePath);
        if(file.is_open()){
            j = nlohmann::json::parse(file);
            file.close();
            for(auto& [key, value] : j.items()){
                std::cout << key << " : " << value << std::endl;
            }
        }
        else{
            file.close();
             std::cout << "open file failed" << std::endl;
        }
    };
}