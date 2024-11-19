# common
file(GLOB common_src "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(common STATIC ${common_src})
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(common PUBLIC tinyxml2)

