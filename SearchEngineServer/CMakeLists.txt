# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../OnlineBase/
    ${CMAKE_CURRENT_SOURCE_DIR}/../OnlineKeyRecommend/
)

# 源文件
file(GLOB search_engine_server_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 生成静态库
add_library(search_engine_server STATIC ${search_engine_server_src})
