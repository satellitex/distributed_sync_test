add_library(server STATIC
    syncServer.cpp
)
target_link_libraries(server
    endpoint
)