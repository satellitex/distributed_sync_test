set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(helper)
add_subdirectory(strage)

add_executable(client-main client.cpp)
target_link_libraries(client-main
    endpoint
    client
    helper
    strage
)

add_executable(server-main server.cpp)
target_link_libraries(server-main
    endpoint
    server
    helper
    strage
)