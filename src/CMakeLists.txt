set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


add_executable(main main.cpp)
target_link_libraries(main
    endpoint
)