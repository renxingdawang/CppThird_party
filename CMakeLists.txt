cmake_minimum_required(VERSION 3.20)
project(TestGrpc)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# gRPC 安装路径（仅 Debug 模式）
set(GRPC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/Debug")

# 头文件路径
include_directories(
    ${GRPC_ROOT}/include
    ${PROJECT_SOURCE_DIR}/gen
)

# 库文件路径
link_directories(
    ${GRPC_ROOT}/lib
)

# 你的源文件
set(PROTO_SRCS
    gen/example.pb.cc
    gen/example.grpc.pb.cc
)
set(APP_SRCS
    TestGrpc.cpp
)
add_executable(TestGrpc
    ${APP_SRCS}
    ${PROTO_SRCS}
)
file(GLOB THIRD_PARTY_LIBS "${PROJECT_SOURCE_DIR}/third_party/Debug/lib/*.lib")
# 链接库
target_link_libraries(TestGrpc
    ${THIRD_PARTY_LIBS}
)
