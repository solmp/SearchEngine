# # Header-only库
# add_library(HeaderOnlyLib INTERFACE)
# target_include_directories(HeaderOnlyLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# # 头文件+源文件库
# file(GLOB SOURCELIB_SRC
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# add_library(SourceLib STATIC ${SOURCELIB_SRC})

# target_include_directories(SourceLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# # 头文件+库文件库
# add_library(PrecompiledLib STATIC IMPORTED)

# set_target_properties(PrecompiledLib PROPERTIES
#     IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libPrecompiledLib.a"
#     INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
# )

# cppjieba
add_library(cppjieba INTERFACE)
target_include_directories(cppjieba INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# tinyxml2
add_library(tinyxml2 STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/tinyxml2.cpp")
target_include_directories(tinyxml2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# nlohmann_json
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# simhash
add_library(simhash INTERFACE)
target_include_directories(simhash INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# llhttp
file(GLOB llhttp_src "${CMAKE_CURRENT_SOURCE_DIR}/src/llhttp/*.c")
add_library(llhttp STATIC ${llhttp_src})
target_include_directories(llhttp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
