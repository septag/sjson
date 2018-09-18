project(test-sjson)
cmake_minimum_required(VERSION 3.0)

add_executable(test-decode "test-decode.c" "../sjson.h")
add_executable(test-encode "test-encode.c" "../sjson.h")
