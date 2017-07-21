include(ExternalProject)
set(EP_PREFIX "${PROJECT_SOURCE_DIR}/external")
set_directory_properties(PROPERTIES
    EP_PREFIX ${EP_PREFIX}
)


################################
#           protobuf           #
################################
find_package(Protobuf 3.3.0)
if (NOT PROTOBUF_FOUND OR NOT PROTOBUF_PROTOC_EXECUTABLE)
    ExternalProject_Add(google_protobuf
            URL https://github.com/google/protobuf/releases/download/v3.3.0/protobuf-cpp-3.3.0.tar.gz
            CONFIGURE_COMMAND ./configure
            BUILD_IN_SOURCE 1
            BUILD_COMMAND $(MAKE)
            INSTALL_COMMAND "" # remove install step
            TEST_COMMAND "" # remove test step
            UPDATE_COMMAND "" # remove update step
            )
    ExternalProject_Get_Property(google_protobuf source_dir)
    set(protobuf_INCLUDE_DIRS ${source_dir}/src)
    set(protobuf_LIBRARIES ${source_dir}/src/.libs/libprotobuf.a)
    set(protoc_EXECUTABLE ${source_dir}/src/protoc)
    file(MAKE_DIRECTORY ${protobuf_INCLUDE_DIRS})
    add_custom_target(protoc DEPENDS google_protobuf)
else ()
    set(protobuf_INCLUDE_DIRS ${PROTOBUF_INCLUDE_DIRS})
    set(protobuf_LIBRARIES ${PROTOBUF_LIBRARY})
    set(protoc_EXECUTABLE ${PROTOBUF_PROTOC_EXECUTABLE})
    add_custom_target(protoc)
endif ()

add_library(protobuf STATIC IMPORTED)
set_target_properties(protobuf PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${protobuf_INCLUDE_DIRS}
        IMPORTED_LOCATION ${protobuf_LIBRARIES}
        )

if (NOT PROTOBUF_FOUND OR NOT PROTOBUF_PROTOC_EXECUTABLE)
    add_dependencies(protobuf google_protobuf protoc)
endif ()

#########################
#         gRPC          #
#########################
find_package(GRPC)
if (NOT GRPC_FOUND)
    ExternalProject_Add(grpc_grpc
            GIT_REPOSITORY "https://github.com/grpc/grpc.git"
            GIT_TAG "v1.3.0"
            BUILD_IN_SOURCE 1
            BUILD_COMMAND $(MAKE)
            CONFIGURE_COMMAND "" # remove configure step
            INSTALL_COMMAND "" # remove install step
            TEST_COMMAND "" # remove test step
            UPDATE_COMMAND "" # remove update step
            )
    ExternalProject_Get_Property(grpc_grpc source_dir)
    set(grpc_INCLUDE_DIR ${source_dir}/include)
    set(grpc_LIBRARY ${source_dir}/libs/opt/libgrpc.so)
    set(grpc_grpc++_LIBRARY ${source_dir}/libs/opt/libgrpc++.so)
    set(grpc_grpc++_reflection_LIBRARY ${source_dir}/libs/opt/libgrpc++_reflection.so)
    set(grpc_CPP_PLUGIN ${source_dir})
    file(MAKE_DIRECTORY ${grpc_INCLUDE_DIR})
    add_custom_target(grpc_cpp_plugin DEPENDS grpc_grpc protoc)
else ()
    set(grpc_INCLUDE_DIR ${GRPC_INCLUDE_DIR})
    set(grpc_LIBRARY ${GRPC_LIBRARY})
    set(grpc_grpc++_LIBRARY ${GRPC_GRPC++_LIBRARY})
    set(grpc_grpc++_reflection_LIBRARY ${GRPC_GRPC++_REFLECTION_LIBRARY})
    set(grpc_CPP_PLUGIN ${GRPC_CPP_PLUGIN})
    add_custom_target(grpc_cpp_plugin DEPENDS protoc)
endif ()

# libgrpc
add_library(grpc SHARED IMPORTED)
set_target_properties(grpc PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${grpc_INCLUDE_DIR}
        IMPORTED_LOCATION ${grpc_LIBRARY}
        )

# libgrpc++
add_library(grpc++ SHARED IMPORTED)
set_target_properties(grpc++ PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${grpc_INCLUDE_DIR}
        IMPORTED_LOCATION ${grpc_grpc++_LIBRARY}
        )

# libgrpc++_reflection
add_library(grpc++_reflection SHARED IMPORTED)
set_target_properties(grpc++_reflection PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${grpc_INCLUDE_DIR}
        IMPORTED_LOCATION ${grpc_grpc++_reflection_LIBRARY}
        )

if (NOT GRPC_FOUND)
    add_dependencies(grpc grpc_grpc)
    add_dependencies(grpc++ grpc_grpc)
    add_dependencies(grpc++_reflection grpc_grpc)
endif ()
