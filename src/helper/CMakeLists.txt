add_library(helper STATIC
    ip_tools.cpp
    thread_pool.cpp
)
target_link_libraries(helper
    pthread
)
