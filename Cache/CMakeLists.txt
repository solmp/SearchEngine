# redis log
file(GLOB redis_log_src "${CMAKE_CURRENT_SOURCE_DIR}/RedisServer.cpp")
add_library(redis_log STATIC ${redis_log_src})
target_link_libraries(redis_log PUBLIC redis++ common)
target_include_directories(redis_log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

# lru log
file(GLOB lru_log_src "${CMAKE_CURRENT_SOURCE_DIR}/LRUCache.cpp")
add_library(lru_log STATIC ${lru_log_src})
target_link_libraries(lru_log PUBLIC nlohmann_json common)
target_include_directories(lru_log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

# cache manager
file(GLOB cache_manager_src "${CMAKE_CURRENT_SOURCE_DIR}/CacheManager.cpp")
add_library(cache_manager STATIC ${cache_manager_src})
target_link_libraries(cache_manager PUBLIC lru_log redis_log)
target_include_directories(cache_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

