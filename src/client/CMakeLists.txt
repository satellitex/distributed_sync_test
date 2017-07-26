add_library(client STATIC
    syncClient.cpp
    commitClient.cpp
    peersClient.cpp
)
target_link_libraries(client
    endpoint
    helper
    grpc++
    pthread
)