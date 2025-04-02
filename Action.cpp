#include "MAACoreInclude/Core.h"
#include "MAACoreInclude/MAAEntity_Tasker.h"

extern "C"{
    MAA_API void TestFunc1(IMAAEntity_Tasker* pTasker){
         int result = pTasker->OCRClick("电池",2000);
    }

    MAA_API int Stratcalculation(IMAAEntity_Tasker* pTasker,int& stop_flag){      //开始演算
        int result = 0;


         auto tryFindGlobal = [&](
            const std::string& textToClick, 
            const std::string& textToFind,
            const std::vector<std::string>& options,
            int nextOptionIndex) -> int {
            int result = 0;
            int flap = 0;
            while (true) {
                flap++;
                result = pTasker->FeatureMatchClick(textToClick.c_str(), 2000);
                std::cout << "Trying to find the global number: " << flap << std::endl;
                std::cout << "result: " << result << std::endl;
                if (result == 3000) {
                    std::cout << "Found the global: " << textToFind << std::endl;
                    std::cout << "result: " << result << std::endl;
                    break;
                }
                if(result !=3000){
                    pTasker->FeatureMatchClick(options[nextOptionIndex].c_str(), 2000);
                }
                if (flap == 10) {
                    std::cout << "Please check the game, it might have lost online?" << std::endl;
                    std::cout << "result: " << result << std::endl;
                    std::cout << "Loop over" << std::endl;
                    stop_flag = 1;
                    return result;
                }
                if (stop_flag != 0) {
                    std::cout << "Please check the game, it might have lost online?" << std::endl;
                    std::cout << "result: " << result << std::endl;
                    std::cout << "Loop over" << std::endl;
                    return result;
                }
            }
            return result;
        };
        std::vector<std::string> imgaePath ={
            "Arknights/gamestart/开始演算.png",
            "Arknights/gamestart/pass1.png",
            "Arknights/gamestart/开始行动.png"
        };



        for (size_t i = 0; i < imgaePath.size(); ++i) {
            int index = i;
            if (stop_flag != 0) {
                return  -1;
            }
            if(i > 0){
                index = i-1;
            }else{
                index = 0;
            }
            int result = tryFindGlobal(imgaePath[i],imgaePath[i],imgaePath,index);
            if (result == 3000) {
                continue; // 如果找到了3000，尝试下一个选项
            }
            break;
        }
        return result;
    }

  MAA_API int TalkForNPC(IMAAEntity_Tasker* pTasker, int& stop_flag) {
    // 与NPC对话

        auto tryTalk = [&](
            const std::string& textToClick, 
            const std::string& textToFind,
            const std::vector<std::string>& options,
            int nextOptionIndex,
            int lastOptionIndex) -> int {
            int result = 0;
            int flap = 0;
            while (true) {
                flap++;
                result = pTasker->OCRClick(textToClick.c_str(), 2000);
                std::cout << "Trying to find the global number: " << flap << std::endl;
                std::cout << "result: " << result << std::endl;
                if (result == 3000) {
                    std::cout << "Found the global: " << textToFind << std::endl;
                    std::cout << "result: " << result << std::endl;
                    break;
                }
                if(result !=3000){
                   std::cout<<"cry the last option"<<std::endl;
                   result = pTasker->OCRClick(options[lastOptionIndex].c_str(), 2000); 
                  
                }
                if(result !=3000){ 
                   std::cout<<"cry the next option"<<std::endl;
                   result = pTasker->OCRClick(options[nextOptionIndex].c_str(), 2000);
                }

                if (flap == 10) {
                    std::cout << "Please check the game, it might have lost online?" << std::endl;
                    std::cout << "result: " << result << std::endl;
                    std::cout << "Loop over" << std::endl;
                    stop_flag = 1;
                    return result;
                }
                if (stop_flag != 0) {
                    std::cout << "Please check the game, it might have lost online?" << std::endl;
                    std::cout << "result: " << result << std::endl;
                    std::cout << "Loop over" << std::endl;
                    return result;
                }
            }
            return result;
        };
        
        auto ScanfCryTalk = [&](
            const std::string& textToClick, 
            const std::string& textToFind,
            const std::vector<std::string>& options
            ) -> int {

            int result = 0;
            int flap = 0;
            while (true) {
                flap++;
                result = pTasker->OCRClick(textToClick.c_str(), 2000);
                std::cout << "Trying to find the global number: " << flap << std::endl;
                std::cout << "result: " << result << std::endl;
                if (result == 3000) {
                    std::cout << "Found the global: " << textToFind << std::endl;
                    std::cout << "result: " << result << std::endl;
                    break;
                }
                if(result !=3000){
                  for(size_t i=0;i<options.size();++i){
                     result = pTasker->OCRClick(options[i].c_str(), 2000);
                     if(result == 3000){
                         break;
                     }
                  }
                }
            
                if (flap == 10) {
                    std::cout << "Please check the game, it might have lost online?" << std::endl;
                    std::cout << "result: " << result << std::endl;
                    std::cout << "Loop over" << std::endl;
                    stop_flag = 1;
                    return result;
                }
                if (stop_flag != 0) {
                    std::cout << "Please check the game, it might have lost online?" << std::endl;
                    std::cout << "result: " << result << std::endl;
                    std::cout << "Loop over" << std::endl;
                    return result;
                }
            }
            return result;
        };
        std::vector<std::string> options = {"好地方", 
                                            "招待客人",
                                            "仓库管理", 
                                            "维护营地", 
                                            "明天一早", 
                                            "这么快就要启程",
                                            "路上",
                                            "探索",
                                            "物资",
                                            "会需要",
                                            "千万",
                                            "谢谢",
                                            "木材",
                                            "木材",
                                            "休息",
                                            "明天"};


        for (size_t i = 0; i < options.size(); ++i) {
            // int lastindex = i;
            // int nextindex = i;
            if (stop_flag != 0) {
                return  -1;
            }
            int lastindex = (i > 0) ? (i-1) : (options.size()-1);
            int nextindex = (i+1) % options.size();
            int result = tryTalk(options[i], options[i], options,lastindex,nextindex);
            if (result == 3000) {
                continue; // 如果找到了3000，尝试下一个选项
            }
            break;
        }
        // for (size_t i = 0; i < options.size(); ++i) {
        //     // int lastindex = i;
        //     // int nextindex = i;
        //     if (stop_flag != 0) {
        //         return  -1;
        //     }
        //     // int lastindex = (i > 0) ? (i-1) : (options.size()-1);
        //     // int nextindex = (i+1) % options.size();
        //     int result = ScanfCryTalk(options[i], options[i], options);
        //     if (result == 3000) {
        //         continue; // 如果找到了3000，尝试下一个选项
        //     }
        //     break;
        // }

        return 0;
    }

    MAA_API int Exit(IMAAEntity_Tasker* pTasker, int& stop_flag){                 //离开关卡
            int result = 0;
            int flap = 0;
            while (true) {
                flap++;
                result = pTasker->FeatureMatchClick("Arknights/gamestart/退出.png", 2000);
                std::cout << "Trying to find the global number: " << flap << std::endl;
                std::cout << "result: " << result << std::endl;
                if (result == 3000) {
                    std::cout << "Found the global: " << "退出" << std::endl;
                    std::cout << "result: " << result << std::endl;
                    break;
                }
                if(result !=3000){
                    result = pTasker->FeatureMatchClick("Arknights/gamestart/退出.png", 2000);
                    result = pTasker->OCRClick("确认离开", 2000);
                   
                }
                if (flap == 10) {
                    std::cout << "Please check the game, it might have lost online?" << std::endl;
                    std::cout << "result: " << result << std::endl;
                    std::cout << "Loop over" << std::endl;
                    stop_flag = 1;
                    return result;
                }
                if (stop_flag != 0) {
                    std::cout << "Please check the game, it might have lost online?" << std::endl;
                    std::cout << "result: " << result << std::endl;
                    std::cout << "Loop over" << std::endl;
                    return result;
                }
            }
            
            return result;
    }

    // MAA_API int StratFight(){           //开始战斗

    // }

    // MAA_API int NextDay(){             //跳过天数

    // }

    // MAA_API int LastTalk(){            //最后的对话

    // }
 
    // MAA_API int DeleteGame(){          //删除本次存档

    // }
}