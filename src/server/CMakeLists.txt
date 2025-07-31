cmake_minimum_required(VERSION 3.20)

project(MyServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(server ${SOURCES})

target_link_libraries(server ${OPENSSL_LIBRARIES})

#  ------- copy ----------
add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/resources/data.json
        $<TARGET_FILE_DIR:server>
)


#  ------- copy ----------
add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/resources/server-1.json
        $<TARGET_FILE_DIR:server>
)


# add_custom_command(TARGET server POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${CMAKE_SOURCE_DIR}/resources/cert.pem
#         $<TARGET_FILE_DIR:server>
# )
# add_custom_command(TARGET server POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${CMAKE_SOURCE_DIR}/resources/key.pem
#         $<TARGET_FILE_DIR:server>
# )



add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/resources/server.crt
        $<TARGET_FILE_DIR:server>
)
add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/resources/server.key
        $<TARGET_FILE_DIR:server>
)