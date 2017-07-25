add_library(handler STATIC
    commitHandler.cpp
)
target_link_libraries(handler
    endpoint
    strage
    client
)