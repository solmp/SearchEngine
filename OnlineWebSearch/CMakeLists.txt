# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../OnlineBase/
    ${CMAKE_CURRENT_SOURCE_DIR}/../RedisLog/
    ${CMAKE_CURRENT_SOURCE_DIR}/../LRULog/
)

# 源文件
file(GLOB online_web_search_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 生成静态库
add_library(online_web_search STATIC ${online_web_search_src})
