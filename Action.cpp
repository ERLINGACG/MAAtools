#include "MAACoreInclude/Core.h"
#include "MAACoreInclude/MAAEntity_Tasker.h"

extern "C"{
    MAA_API void TestFunc1(IMAAEntity_Tasker* pTasker){
        //  int result = pTasker->OCRClick("电池",2000);
        // 
        std::vector<int> beginPos = {300,300,40,40};
        std::vector<int> endPos =   {500,300,40,40};
        int result = pTasker->Swipe(beginPos, endPos, 200);
        int result2 = pTasker->Click(1004,619,185,96);
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
         constexpr int MAX_RETRY = 10;
            constexpr int SUCCESS_CODE = 3000;
            constexpr int TIMEOUT = 2000;
            int last_result = 0;
            int result = 0;
            const std::vector<std::function<int(int t)>> Tsteps = {
                {[&](int t){ return pTasker->OCRClick("好地方", t); }},
                {[&](int t){ return pTasker->OCRClick("招待客人", t); }},
                {[&](int t){ return pTasker->OCRClick("仓库管理", t); }},
                {[&](int t){ return pTasker->OCRClick("维护营地", t); }},
                {[&](int t){ return pTasker->OCRClick("明天一早", t); }},
                {[&](int t){ return pTasker->OCRClick("这么快就要启程", t); }},
                {[&](int t){ return pTasker->OCRClick("路上", t); }},
                {[&](int t){ return pTasker->OCRClick("探索", t); }},
                {[&](int t){ return pTasker->OCRClick("物资", t); }},
                {[&](int t){ return pTasker->OCRClick("会需要", t); }},
                {[&](int t){ return pTasker->OCRClick("千万", t); }},
                {[&](int t){ return pTasker->OCRClick("谢谢", t); }},
                {[&](int t){ return pTasker->OCRClick("木材", t); }},
                {[&](int t){ return pTasker->OCRClick("木材", t); }},
                {[&](int t){ return pTasker->OCRClick("休息", t); }},
                {[&](int t){ return pTasker->FeatureMatchClick("Arknights/gamestart/明天还有很多要忙的.png", t);}},
                {[&](int t){ return pTasker->FeatureMatchClick("Arknights/gamestart/退出.png", t); }},
                {[&](int t){ return pTasker->OCRClick("确认离开", t); }},
            };
        

        auto tryFindGlobal = [&](std::vector<std::function<int(int t)>> Asteps) -> int {
               for(int i=0;i<Asteps.size();i++){
                   int start_loop =0;
                   while(start_loop<=MAX_RETRY){
                       result = Asteps[i](TIMEOUT);
                       if(stop_flag != 0) return -1;
                       std::cout<<"fight step "<<i<<std::endl;
                       start_loop++;
                       if(result != SUCCESS_CODE && i!= 0 && i!= Asteps.size()-1){
                           std::cout<<"retry fight step "<<i<<std::endl;
                           Asteps[(i-1)%Asteps.size()](TIMEOUT);
                           Asteps[(i+1)%Asteps.size()](TIMEOUT);
                       }
                       if(result != SUCCESS_CODE && i==0){
                         std::cout<<"retry fight step "<<i<<std::endl;
                         Asteps[i+1](TIMEOUT);
                       }
                       
                       if(result != SUCCESS_CODE && i==Asteps.size()-1|| i==Asteps.size()-2 ){
                         std::cout<<"retry fight step "<<i<<std::endl;

                         Asteps[i-1](TIMEOUT);
                       }
                       if(result == SUCCESS_CODE || start_loop > 10){ // 找到了3000或循环次数大于10，尝试下一个选项
                        
                           break;
                       }
                   }
               }
               return 0;
        };
        tryFindGlobal(Tsteps);
      
        return 0;
    }

    MAA_API int Exit(IMAAEntity_Tasker* pTasker, int& stop_flag){                 //离开关卡
            constexpr int MAX_RETRY = 10;
            constexpr int SUCCESS_CODE = 3000;
            constexpr int TIMEOUT = 2000;
            int last_result = 0;
            int result = 0;
            // int result = 0;
            // int flap = 0;
            // while (true) {
            //     flap++;
            //     result = pTasker->FeatureMatchClick("Arknights/gamestart/退出.png", 2000);
            //     std::cout << "Trying to find the global number: " << flap << std::endl;
            //     std::cout << "result: " << result << std::endl;
            //     if (result == 3000) {
            //         std::cout << "Found the global: " << "退出" << std::endl;
            //         std::cout << "result: " << result << std::endl;
            //         break;
            //     }
            //     if(result !=3000){
            //         result = pTasker->FeatureMatchClick("Arknights/gamestart/退出.png", 2000);
            //         result = pTasker->OCRClick("确认离开", 2000);
                   
            //     }
            //     if (flap == 10) {
            //         std::cout << "Please check the game, it might have lost online?" << std::endl;
            //         std::cout << "result: " << result << std::endl;
            //         std::cout << "Loop over" << std::endl;
            //         stop_flag = 1;
            //         return result;
            //     }
            //     if (stop_flag != 0) {
            //         std::cout << "Please check the game, it might have lost online?" << std::endl;
            //         std::cout << "result: " << result << std::endl;
            //         std::cout << "Loop over" << std::endl;
            //         return result;
            //     }
            // }
              const std::vector<std::function<int(int t)>> Tsteps2 = {
                 {[&](int t){ return pTasker->FeatureMatchClick("Arknights/gamestart/退出.png", t); }},
                 {[&](int t){ return pTasker->OCRClick("确认离开", t); }},
              };
            
            // return result;
            auto tryFindGlobal = [&](std::vector<std::function<int(int t)>> Asteps) -> int {
               for(int i=0;i<Asteps.size();i++){
                   int start_loop =0;
                   while(start_loop<=MAX_RETRY){
                       result = Asteps[i](TIMEOUT);
                       if(stop_flag != 0) return -1;
                       std::cout<<"fight step "<<i<<std::endl;
                       start_loop++;
                       if(result != SUCCESS_CODE && i==0){
                           std::cout<<"retry fight step "<<i<<std::endl;
                           Asteps[1](TIMEOUT);
                         
                       }
                       if(result != SUCCESS_CODE && i==1){
                         std::cout<<"retry fight step "<<i<<std::endl;
                         Asteps[0](TIMEOUT);
                       }
                       if(result == SUCCESS_CODE){
                        
                           break;
                       }
                   }
               }
               return 0;
            };
            tryFindGlobal(Tsteps2);
            return 0;
    }
    
   MAA_API void MoveSwipe(IMAAEntity_Tasker* pTasker, int& stop_flag){                 //移动滑动
        pTasker->Swipe({300,300,40,40},{500,300,40,40},200);
   }


   MAA_API int StratFight(IMAAEntity_Tasker* pTasker, int& stop_flag) {

            constexpr int MAX_RETRY = 10;
            constexpr int SUCCESS_CODE = 3000;
            constexpr int TIMEOUT = 2000;
            int last_result = 0;
            int result = 0;
            const std::vector<std::function<int(int t)>> Tsteps1 = {
                { [&](int t){ return pTasker->OCRClick("灌木林", t); }, },
                { [&](int t){ return pTasker->OCRClick("开始", t); }, },
                { [&](int t){ return pTasker->OCRClick("开始", t); }, },
                { [&](int t){ return pTasker->FeatureMatchClick("Arknights/gamestart/退出.png", t); }, },
                { [&](int t){ return pTasker->OCRClick("确认离开", t); }, },
                { [&](int t){ return pTasker->OCRClick("灌木林", t); }, },
            };
            
            const std::vector<std::function<int(int t)>> Tsteps2 = {
                { [&](int t){ return pTasker->OCRClick("聚羽之地", t); }, },
                { [&](int t){ return pTasker->OCRClick("开始", t); }, },
                { [&](int t){ return pTasker->OCRClick("开始", t); }, },
                { [&](int t){ return pTasker->FeatureMatchClick("Arknights/gamestart/确认.png", t); }},
                { [&](int t){ return pTasker->FeatureMatchClick("Arknights/gamestart/退出.png", t); }},
                { [&](int t){ return pTasker->OCRClick("确认离开", t); }, },
                { [&](int t){ return pTasker->OCRClick("行动结束", t); }, },
                {[&](int t){std::cout<<"delay 10s"<<std::endl ; Sleep(10000);std::cout<<"delay is over"<<std::endl ;
                return pTasker->FeatureMatchClick("Arknights/gamestart/下一日.png", t);}},
            };
            auto tryFindGlobal = [&](std::vector<std::function<int(int t)>> Asteps) -> int {
               for(int i=0;i<Asteps.size();i++){
                   int start_loop =0;
                   while(start_loop<=MAX_RETRY){
                       start_loop++;
                       result = Asteps[i](TIMEOUT);
                       if(stop_flag != 0) return -1;
                       std::cout<<"fight step "<<i<<std::endl;
                       start_loop++;
                       if(result != SUCCESS_CODE && i!= 0 && i!= Asteps.size()-1){
                           std::cout<<"retry fight step "<<i<<std::endl;
                           Asteps[(i-1)%Asteps.size()](TIMEOUT);
                           Asteps[(i+1)%Asteps.size()](TIMEOUT);
                       }
                        if(result != SUCCESS_CODE && i==0){
                         std::cout<<"retry fight step "<<i<<std::endl;
                         pTasker->Swipe({300,300,40,40},{500,300,40,40},200);
                       }
                       if(result != SUCCESS_CODE && i==Asteps.size()-1){
                         std::cout<<"retry fight step "<<i<<std::endl;
                         Asteps[i-1](TIMEOUT);
                       }
                       if(result == SUCCESS_CODE || start_loop > 10){
                           break;
                       }
                   }
               }
               return 0;
            };
            tryFindGlobal(Tsteps1);
            tryFindGlobal(Tsteps2);
           
            return 0;
    }

    MAA_API int NextDay(IMAAEntity_Tasker* pTasker, int& stop_flag){ 
         const std::vector<std::function<int(int t)>> Tsteps_NextDay = {
            // {[&](int t){return pTasker->FeatureMatchClick("Arknights/gamestart/第二日.png", t);}},
            {[&](int t){return pTasker->Click(1085, 5, 165, 161);}},
            {[&](int t){return pTasker->OCRClick("消磨", t);}},
            {[&](int t){return pTasker->OCRClick("确认", t);}},
            {[&](int t){std::cout<<"delay 10s"<<std::endl ; Sleep(5000);std::cout<<"delay is over"<<std::endl ;return 3000;}},
            {[&](int t){return pTasker->Click(1085, 5, 165, 161);}},
         };

                    //跳过天数
        constexpr int MAX_RETRY = 10;
        constexpr int SUCCESS_CODE = 3000;
        constexpr int TIMEOUT = 2000;
        int last_result = 0;
        int result = 0;
        auto tryFindGlobal = [&](std::vector<std::function<int(int t)>> Asteps) -> int {
               for(int i=0;i<Asteps.size();i++){
                   int start_loop =0;
                   while(start_loop<=MAX_RETRY){
                       start_loop++;
                       result = Asteps[i](TIMEOUT);
                       if(stop_flag != 0) return -1;
                       std::cout<<"fight step "<<i<<std::endl;
                       if(result != SUCCESS_CODE && i!= 0 && i!= Asteps.size()-1){
                           std::cout<<"retry fight step "<<i<<std::endl;
                           Asteps[(i-1)%Asteps.size()](TIMEOUT);
                           Asteps[(i+1)%Asteps.size()](TIMEOUT);
                       }
                       if(result != SUCCESS_CODE && i==0){
                            pTasker->FeatureMatchClick("Arknights/gamestart/下一日.png", TIMEOUT);
                       }
                       if(result == SUCCESS_CODE || start_loop > 10){
                           break;
                       }
                   }
               }
               return 0;
            };
            tryFindGlobal(Tsteps_NextDay);
            return 0;   
            // Sleep(10000);
    }  
    MAA_API int  SettlementDay(IMAAEntity_Tasker* pTasker, int& stop_flag){ //结算日
        constexpr int MAX_RETRY = 10;
        constexpr int SUCCESS_CODE = 3000;
        constexpr int TIMEOUT = 2000;
        int last_result = 0;
        int result = 0;
        const std::vector<std::function<int(int t)>> Steps = {
            {[&](int t){return pTasker->OCRClick("生息日", t);}},
            {[&](int t){return pTasker->OCRClick("开启今日", t);}},

        };


        auto tryFindGlobal = [&](std::vector<std::function<int(int t)>> Asteps) -> int {
               for(int i=0;i<Asteps.size();i++){
                   int start_loop =0;
                   while(start_loop<=MAX_RETRY){
                       start_loop++;
                       result = Asteps[i](TIMEOUT);
                       if(stop_flag != 0) return -1;
                       std::cout<<"fight step "<<i<<std::endl;
                       if(result != SUCCESS_CODE && i!= 0 && i!= Asteps.size()-1){
                           std::cout<<"retry fight step "<<i<<std::endl;
                           Asteps[(i-1)%Asteps.size()](TIMEOUT);
                    
                       }
                       if(result != SUCCESS_CODE && i==0){
                           Asteps[i+1](TIMEOUT);
                       }
                       if(result != SUCCESS_CODE && i==Asteps.size()-1){
                           Asteps[i-1](TIMEOUT);
                       }
                       if(result == SUCCESS_CODE || start_loop > 10){
                           break;
                       }
                   }
               }
               return 0;
            };

        tryFindGlobal(Steps);

        return 0;
    }
 
    MAA_API int TalkForNPCSecond(IMAAEntity_Tasker* pTasker, int& stop_flag){            //第二次与NPC对话
        constexpr int MAX_RETRY = 10;
        constexpr int SUCCESS_CODE = 3000;
        constexpr int TIMEOUT = 2000;
        int last_result = 0;
        int result = 0;
        const std::vector<std::function<int(int t)>> Steps = {
            { [&](int t){ return pTasker->OCRClick("陌域", t); }},
            { [&](int t){ return pTasker->OCRClick("提升", t); }},
            { [&](int t){ return pTasker->OCRClick("看看", t); }},
        };

       auto tryFindGlobal = [&](std::vector<std::function<int(int t)>> Asteps) -> int {
               for(int i=0;i<Asteps.size();i++){
                   int start_loop =0;
                   while(start_loop<=MAX_RETRY){
                       start_loop++;
                       result = Asteps[i](TIMEOUT);
                       if(stop_flag != 0) return -1;
                       std::cout<<"fight step "<<i<<std::endl;
                       if(result != SUCCESS_CODE && i!= 0 && i!= Asteps.size()-1){
                           std::cout<<"retry fight step "<<i<<std::endl;
                           Asteps[(i-1)%Asteps.size()](TIMEOUT);
                           Asteps[(i+1)%Asteps.size()](TIMEOUT);
                    
                       }
                       if(result != SUCCESS_CODE && i==0){
                           Asteps[i+1](TIMEOUT);
                       }
                       if(i >0 && result != SUCCESS_CODE && i==Asteps.size()-1){
                           Asteps[i-1](TIMEOUT);
                       }
                       if(result == SUCCESS_CODE || start_loop > 10){
                           break;
                       }
                   }
               }
               return 0;
            };
        tryFindGlobal(Steps);
        return 0;
    }
 
    MAA_API int DeleteArchive(IMAAEntity_Tasker* pTasker, int& stop_flag){          //删除本次存档
        constexpr int MAX_RETRY = 10;
        constexpr int SUCCESS_CODE = 3000;
        constexpr int TIMEOUT = 2000;
        int last_result = 0;
        int result = 0; 
        const std::vector<std::function<int(int t)>> Steps = {
            {[&](int t){pTasker->Click(1004,619,185,96);return 3000;}},
            {[&](int t){return pTasker->OCRClick("删除存档", t);}},
            {[&](int t){Sleep(5000); pTasker->Click(925,464,121,36); return 3000;}},
            {[&](int t){Sleep(5000); pTasker->Click(925,464,121,36); return 3000;}},

        };
        auto tryFindGlobal = [&](std::vector<std::function<int(int t)>> Asteps) -> int {
               for(int i=0;i<Asteps.size();i++){
                   int start_loop =0;
                   while(start_loop<=MAX_RETRY){
                       start_loop++;
                       result = Asteps[i](TIMEOUT);
                       if(stop_flag != 0) return -1;
                       std::cout<<"fight step "<<i<<std::endl;
                       if(result != SUCCESS_CODE && i!= 0 && i!= Asteps.size()-1){
                           std::cout<<"retry fight step "<<i<<std::endl;
                          Asteps[(i-1)%Asteps.size()](TIMEOUT);
                          Asteps[(i+1)%Asteps.size()](TIMEOUT);
                    
                       }
                    //    if(result != SUCCESS_CODE && i==0){
                    //        Asteps[i+1](TIMEOUT);
                    //    }
                    //    if(result == SUCCESS_CODE || i==Asteps.size()-1){
                    //        Asteps[i-1](TIMEOUT);
                    //    }
                       if(result == SUCCESS_CODE || start_loop > 10){
                           break;
                       }
                   }
               }
               return 0;
            };
            tryFindGlobal(Steps);
            return 0;
    }
}