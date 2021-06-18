cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
project(calculator)


file(GLOB SRC src/*.cpp)
add_executable(calculator ${SRC})


target_include_directories(calculator PUBLIC include/)
