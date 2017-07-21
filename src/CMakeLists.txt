set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


add_executable(client client.cpp)
target_link_libraries(client
    endpoint
)