# search_engine_server
file(GLOB search_engine_server_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(search_engine_server STATIC ${search_engine_server_src})
target_link_libraries(search_engine_server PUBLIC online_web_search online_key_recommend)
target_include_directories(search_engine_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
