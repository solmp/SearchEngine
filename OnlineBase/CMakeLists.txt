# online_base
file(GLOB online_base_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(online_base STATIC ${online_base_src})
target_link_libraries(online_base PUBLIC timer llhttp)
target_include_directories(online_base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

