compile_proto_to_grpc_cpp(endpoint.proto)

add_library(endpoint
        endpoint.pb.cc
        endpoint.grpc.pb.cc
)

target_link_libraries(endpoint
        protobuf
        grpc
        grpc++
        grpc++_reflection
)
