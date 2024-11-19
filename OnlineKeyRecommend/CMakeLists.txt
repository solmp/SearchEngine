# online_key_recommend
file(GLOB online_key_recommend_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(online_key_recommend STATIC ${online_key_recommend_src})
target_link_libraries(online_key_recommend PUBLIC online_base)
target_include_directories(online_key_recommend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
