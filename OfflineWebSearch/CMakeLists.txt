# offline_web_search
file(GLOB offline_web_search_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(offline_web_search STATIC ${offline_web_search_src})
target_link_libraries(offline_web_search PUBLIC simhash common)
target_include_directories(offline_web_search PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
