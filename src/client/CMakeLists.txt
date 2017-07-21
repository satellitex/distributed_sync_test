add_library(client
    syncClient.cpp
)
target_link_libraries(client
    endpoint
)