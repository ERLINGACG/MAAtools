cmake_minimum_required(VERSION 3.10)
project(MyProject)


set(CMAKE_BUILD_TYPE Release) 
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto -march=native")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

# # 设置C++标准
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-adhln -g")  # 生成带源码的混合汇编
# set(CMAKE_ASM_LISTING_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/asm_output)
# file(MAKE_DIRECTORY ${CMAKE_ASM_LISTING_OUTPUT_DIRECTORY})


# 添加包含目录
include_directories(./include/)

# 添加链接库目录
link_directories(./lib/)

# 添加源文件
#  add_executable(main2 Sample_main.cpp)
# add_executable(main3 jsonTest.cpp)
# add_executable(main4 EcosystemSimulationCore.cpp)
# add_library(MAAtest1 SHARED MAAtest2.cpp)
# add_library(Test3 SHARED Test3.cpp)
add_library(MAACoreAPI SHARED 
  MAACoreAPI.cpp 
  MAAEntity_Controller.cpp
  MAAEntity_Resource.cpp 
  MAAEntity_Tasker.cpp
  Arknights.cpp
  )
add_library(Action SHARED 
    Action.cpp
    MAACoreAPI.cpp 
    MAAEntity_Tasker.cpp
    MAAEntity_Controller.cpp
    MAAEntity_Resource.cpp 
)
target_compile_options(MAACoreAPI PRIVATE
    $<$<CONFIG:Release>:-O3 -flto -march=native>
)
target_compile_options(Action PRIVATE
    $<$<CONFIG:Release>:-O3 -flto -march=native>
)
# target_compile_options(MAACoreAPI PRIVATE
#   -save-temps=obj  # 生成.s和.ii中间文件
#   -fverbose-asm    # 生成带注释的汇编
# )
# set_target_properties(MAACoreAPI PROPERTIES
#     COMPILE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/asm_temp"
# )
# 设置链接库
# target_link_libraries(MAAtest1 MaaFramework MaaToolkit)
# target_link_libraries(main4 MaaFramework MaaToolkit)
target_link_libraries(MAACoreAPI MaaFramework MaaToolkit)
target_link_libraries(Action MaaFramework MaaToolkit)
# set_target_properties(MAACoreAPI PROPERTIES COMPILE_FLAGS "-S")
target_compile_definitions(MAACoreAPI PRIVATE MAA_API_EXPORT)
target_compile_definitions(Action PRIVATE MAA_API_EXPORT)
# 开启调试信息





# set(CMAKE_BUILD_TYPE Debug)
# set_target_properties(MAAEntity_C PROPERTIES DEFINE_SYMBOL MAA_API_EXPORT)
target_compile_definitions(MAACoreAPI PRIVATE 
    MAA_API_EXPORT  # 重要！启用导出符号
)
target_compile_definitions(Action PRIVATE 
    MAA_API_EXPORT  # 重要！启用导出符号
)
target_include_directories(MAACoreAPI PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(Action PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)
# 如果需要颜色输出，可以使用以下命令在命令行中构建时指定（CMake本身不支持在构建系统中直接设置颜色输出）
# cmake --build . -- -fdiagnostics-color=always
