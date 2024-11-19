# offline_key_recommend
file(GLOB offline_key_recommend_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(offline_key_recommend STATIC ${offline_key_recommend_src})
target_link_libraries(offline_key_recommend PUBLIC common)
target_include_directories(offline_key_recommend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
