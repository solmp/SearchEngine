cmake_minimum_required(VERSION 3.10)

project(SearchEngine)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 源文件列表
# file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# 测试源文件列表
file(GLOB TEST_FILES "${CMAKE_SOURCE_DIR}/test/*.cpp")

# 创建可执行文件
# add_executable(YourExecutableName ${SRC_FILES})

# 链接库（如果有）
# target_link_libraries(YourExecutableName YourLibraries)

# 创建测试
enable_testing()
# 针对每个测试文件创建单独的可执行程序和测试
list(APPEND public_src_file "src/Configuration.cpp")
foreach(test_file ${TEST_FILES})
    get_filename_component(test_name ${test_file} NAME_WE)
    string(REGEX REPLACE "test/test(.*).cpp" "src/\\1.cpp" src_file ${test_file})
    if(EXISTS ${src_file})
        add_executable(${test_name} ${test_file} ${src_file} ${public_src_file})
    else()
        add_executable(${test_name} ${test_file} ${public_src_file})
    endif()
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)