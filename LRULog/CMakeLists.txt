# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../LRULog/
)

# 源文件
file(GLOB lru_log_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 生成静态库
add_library(lru_log STATIC ${lru_log_src})
