cmake_minimum_required(VERSION 3.0)
project(wsw_md_server)#工程名字

#设置debug模式，如果没有这一行将不能调试设断点
#set(CMAKE_BUILD_TYPE "Debug")

# 设置cmake的全局变量/设置可执行文件最终的存储路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置头文件搜索路径,相当于makefile里面的-I
# include_directories(${PROJECT_SOURCE_DIR}/include)
# 配置库文件搜索路径
# link_directories()

#设置需要编译的源文件列表
set(SRC_LIST ./muduo_test.cpp)
# 把指定路径(.)下的所有源文件名字放入变量名SRC_LIST里面
# aux_source_directory(. SRC_LIST)
# 把src文件夹里面的所有源文件都放入变量SRC_LIST里面
# aux_source_directory(src SRC_LIST)

# 表示生成可执行文件wsw_muduo_server，由SRC_LIST变量所定义的源文件编译而来
add_executable(wsw_muduo_server ${SRC_LIST})
# add_executable(wsw_muduo_server muduo_test.cpp)
# 表示server这个目标程序，需要连接muduo_net muduo_base pthread这三个库文件
target_link_libraries(wsw_muduo_server muduo_net muduo_base pthread)