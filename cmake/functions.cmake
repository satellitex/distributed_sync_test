function(compile_proto_to_cpp PROTO)
  string(REGEX REPLACE "\\.proto$" ".pb.h" GEN_PB_HEADER ${PROTO})
  string(REGEX REPLACE "\\.proto$" ".pb.cc" GEN_PB ${PROTO})
  string(REGEX REPLACE "\\.proto$" "proto_h" GEN_TARGET ${PROTO})
  add_custom_command(
          OUTPUT ${IROHA_SCHEMA_DIR}/${GEN_PB_HEADER} ${IROHA_SCHEMA_DIR}/${GEN_PB}
          COMMAND "${protoc_EXECUTABLE}" --cpp_out=${IROHA_SCHEMA_DIR} ${PROTO}
          DEPENDS protoc
          WORKING_DIRECTORY ${IROHA_SCHEMA_DIR})

  add_library(${GEN_TARGET}
          "${IROHA_SCHEMA_DIR}/${GEN_PB_HEADER}"
          "${IROHA_SCHEMA_DIR}/${GEN_PB}")
  target_include_directories(${GEN_TARGET} PUBLIC
          ${protobuf_INCLUDE_DIRS}
          ${IROHA_SCHEMA_DIR}
          )
  target_link_libraries(${GEN_TARGET}
          ${protobuf_LIBRARIES}
          )

  set_property(TARGET protobuf APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${GEN_TARGET})
  add_dependencies(protobuf ${GEN_TARGET})
endfunction()

function(compile_proto_to_grpc_cpp PROTO)
  string(REGEX REPLACE "\\.proto$" ".pb.h" GEN_PB_HEADER ${PROTO})
  string(REGEX REPLACE "\\.proto$" ".pb.cc" GEN_PB ${PROTO})
  string(REGEX REPLACE "\\.proto$" ".grpc.pb.h" GEN_GRPC_PB_HEADER ${PROTO})
  string(REGEX REPLACE "\\.proto$" ".grpc.pb.cc" GEN_GRPC_PB ${PROTO})
  string(REGEX REPLACE "\\.proto$" "proto_h" GEN_TARGET ${PROTO})
  add_custom_command(
          OUTPUT ${IROHA_SCHEMA_DIR}/${GEN_PB_HEADER} ${IROHA_SCHEMA_DIR}/${GEN_PB} ${IROHA_SCHEMA_DIR}/${GEN_GRPC_PB_HEADER} ${IROHA_SCHEMA_DIR}/${GEN_GRPC_PB}
          COMMAND "${protoc_EXECUTABLE}" --cpp_out=${IROHA_SCHEMA_DIR} ${PROTO}
          COMMAND "${protoc_EXECUTABLE}" --grpc_out=${IROHA_SCHEMA_DIR} --plugin=protoc-gen-grpc="${grpc_CPP_PLUGIN}" ${PROTO}
          DEPENDS grpc_cpp_plugin
          WORKING_DIRECTORY ${IROHA_SCHEMA_DIR})

  add_library(${GEN_TARGET}
          "${IROHA_SCHEMA_DIR}/${GEN_PB_HEADER}"
          "${IROHA_SCHEMA_DIR}/${GEN_PB}"
          "${IROHA_SCHEMA_DIR}/${GEN_GRPC_PB_HEADER}"
          "${IROHA_SCHEMA_DIR}/${GEN_GRPC_PB}")
  target_include_directories(${GEN_TARGET} PUBLIC
          ${protobuf_INCLUDE_DIRS}
          ${grpc_INCLUDE_DIR}
          ${IROHA_SCHEMA_DIR}
          )
  target_link_libraries(${GEN_TARGET}
          ${protobuf_LIBRARIES}
          ${grpc_LIBRARY}
          )

  set_property(TARGET protobuf APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${GEN_TARGET})
  set_property(TARGET grpc APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${GEN_TARGET})
  set_property(TARGET grpc++ APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${GEN_TARGET})
  add_dependencies(protobuf ${GEN_TARGET})
  add_dependencies(grpc ${GEN_TARGET})
endfunction()