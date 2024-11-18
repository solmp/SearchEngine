# 设置测试运行路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)

# 为每个模块添加测试
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../OfflineKeyRecommend/
    ${CMAKE_CURRENT_SOURCE_DIR}/../OfflineWebSearch/
    ${CMAKE_CURRENT_SOURCE_DIR}/../OnlineBase/
    ${CMAKE_CURRENT_SOURCE_DIR}/../OnlineKeyRecommend/
    ${CMAKE_CURRENT_SOURCE_DIR}/../OnlineWebSearch/
    ${CMAKE_CURRENT_SOURCE_DIR}/../SearchEngineServer/
    ${CMAKE_CURRENT_SOURCE_DIR}/../LogBase/
    ${CMAKE_CURRENT_SOURCE_DIR}/../RedisLog/
)

# 3rdparty
file(GLOB TEST_3RDPART_SRC "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/test*.cpp")
foreach(test_file ${TEST_3RDPART_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE cppjieba tinyxml2 nlohmann_json simhash llhttp redis++)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# Common
file(GLOB TEST_COMMON_SRC "${CMAKE_CURRENT_SOURCE_DIR}/Common/test*.cpp")
foreach(test_file ${TEST_COMMON_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE common)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# OfflineKeyRecommend
file(GLOB TEST_OFFLINE_KEY_RECOMMEND_SRC "${CMAKE_CURRENT_SOURCE_DIR}/OfflineKeyRecommend/test*.cpp")
foreach(test_file ${TEST_OFFLINE_KEY_RECOMMEND_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE offline_key_recommend common)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# OfflineWebSearch
file(GLOB TEST_OFFLINE_WEB_SEARCH_SRC "${CMAKE_CURRENT_SOURCE_DIR}/OfflineWebSearch/test*.cpp")
foreach(test_file ${TEST_OFFLINE_WEB_SEARCH_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE offline_web_search common)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# OnlineBase
file(GLOB TEST_ONLINE_BASE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/OnlineBase/test*.cpp")
foreach(test_file ${TEST_ONLINE_BASE_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE online_base common)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# SearchEngineServer
file(GLOB TEST_SEARCH_ENGINE_SERVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/SearchEngineServer/test*.cpp")
foreach(test_file ${TEST_SEARCH_ENGINE_SERVER_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE 
        search_engine_server online_key_recommend online_web_search online_base common)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# OnlineKeyRecommend
file(GLOB TEST_ONLINE_KEY_RECOMMEND_SRC "${CMAKE_CURRENT_SOURCE_DIR}/OnlineKeyRecommend/test*.cpp")
foreach(test_file ${TEST_ONLINE_KEY_RECOMMEND_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE online_key_recommend online_base common)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# OnlineWebSearch
file(GLOB TEST_ONLINE_WEB_SEARCH_SRC "${CMAKE_CURRENT_SOURCE_DIR}/OnlineWebSearch/test*.cpp")
foreach(test_file ${TEST_ONLINE_WEB_SEARCH_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE online_web_search online_base common)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# RedisLog
file(GLOB TEST_REDIS_LOG_SRC "${CMAKE_CURRENT_SOURCE_DIR}/RedisLog/test*.cpp")
foreach(test_file ${TEST_REDIS_LOG_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE redis_log redis++ common)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()


