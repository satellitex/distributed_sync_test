add_library(server
    syncServer.cpp
)
target_link_libraries(server
    endpoint
)