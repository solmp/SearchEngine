# 包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 源文件
file(GLOB common_src "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 生成静态库
add_library(common STATIC ${common_src})

# 链接第三方库（根据需要）
target_link_libraries(common PRIVATE cppjieba tinyxml2 nlohmann_json simhash)

