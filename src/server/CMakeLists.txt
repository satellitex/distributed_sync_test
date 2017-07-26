add_library(server STATIC
    syncServer.cpp
    commitServer.cpp
    peersServer.cpp
)
target_link_libraries(server
    endpoint
    strage
    helper
    grpc++
    pthread
    handler
)