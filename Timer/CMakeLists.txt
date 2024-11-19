# timer
file(GLOB timer_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(timer STATIC ${timer_src})
target_link_libraries(timer PUBLIC cache_manager)
target_include_directories(timer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
