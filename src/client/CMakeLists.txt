add_library(client STATIC
    syncClient.cpp
)
target_link_libraries(client
    endpoint
)