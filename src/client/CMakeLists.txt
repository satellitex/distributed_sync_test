add_library(client STATIC
    syncClient.cpp
    commitClient.cpp
)
target_link_libraries(client
    endpoint
    helper
    grpc++
    pthread
)