# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/include
)

# 源文件
file(GLOB offline_key_recommend_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 生成静态库
add_library(offline_key_recommend STATIC ${offline_key_recommend_src})
