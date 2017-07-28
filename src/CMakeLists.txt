set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(helper)
add_subdirectory(strage)
add_subdirectory(handler)


add_executable(root-main root_main.cpp)
target_link_libraries(root-main
    client
    server
    endpoint
    pthread
    strage
)

add_executable(child-main child_main.cpp)
target_link_libraries(child-main
    server
    pthread
    client
    helper
)