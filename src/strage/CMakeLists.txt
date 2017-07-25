add_library(strage STATIC
        strage.cpp
        validator.cpp
)
target_link_libraries(strage
        endpoint
)