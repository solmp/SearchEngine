# online_web_search
file(GLOB online_web_search_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(online_web_search STATIC ${online_web_search_src})
target_link_libraries(online_web_search PUBLIC online_base)
target_include_directories(online_web_search PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
