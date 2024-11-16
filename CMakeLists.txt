cmake_minimum_required(VERSION 3.10)

project(SearchEngine)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/3rdparty)

# 源文件列表
# file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# 测试源文件列表
file(GLOB TEST_FILES "${CMAKE_SOURCE_DIR}/test/*.cpp" "${CMAKE_SOURCE_DIR}/test/3rdparty/*.cpp")

# 创建可执行文件
# add_executable(YourExecutableName ${SRC_FILES})

# 链接库（如果有）
# target_link_libraries(YourExecutableName YourLibraries)

# 创建测试
enable_testing()
# 针对每个测试文件创建单独的可执行程序和测试
list(APPEND PUBLIC_SRC_FILE
    "${CMAKE_SOURCE_DIR}/src/3rdparty/tinyxml2.cpp"
    "${CMAKE_SOURCE_DIR}/src/Configuration.cpp"
    "${CMAKE_SOURCE_DIR}/src/DirScanner.cpp"
    "${CMAKE_SOURCE_DIR}/src/WebPage.cpp"
    "${CMAKE_SOURCE_DIR}/src/SplitToolCppJieba.cpp"
)

add_library(PUBLIC_LIB STATIC ${PUBLIC_SRC_FILE})

foreach(test_file ${TEST_FILES})
    get_filename_component(test_name ${test_file} NAME_WE)
    string(REGEX REPLACE "test/test(.*).cpp" "src/\\1.cpp" src_file ${test_file})
    if(EXISTS ${src_file})
        list(FIND PUBLIC_SRC_FILE "${src_file}" is_exist)
        if(${is_exist} EQUAL -1)
            add_executable(${test_name} ${test_file} ${src_file})
        else()
            add_executable(${test_name} ${test_file})
        endif()
    else()
        add_executable(${test_name} ${test_file})
    endif()
    target_link_libraries(${test_name} PUBLIC_LIB)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)