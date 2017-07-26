add_library(server STATIC
    syncServer.cpp
    commitServer.cpp
)
target_link_libraries(server
    endpoint
    strage
    helper
    grpc++
    pthread
    handler
)