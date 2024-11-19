cmake_minimum_required(VERSION 3.15)
project(SearchEngine)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

enable_testing()

# 添加子目录
add_subdirectory(3rdparty)
add_subdirectory(Common)
add_subdirectory(OfflineKeyRecommend)
add_subdirectory(OfflineWebSearch)
add_subdirectory(OnlineBase)
add_subdirectory(OnlineKeyRecommend)
add_subdirectory(OnlineWebSearch)
add_subdirectory(SearchEngineServer)
add_subdirectory(LRULog)
add_subdirectory(RedisLog)
add_subdirectory(Timer)
add_subdirectory(test)
