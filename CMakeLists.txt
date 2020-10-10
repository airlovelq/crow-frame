cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -g2 -ggdb -fopenmp -ldl")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -Wall -g2 -ggdb -fopenmp -ldl")
add_definitions(-D _FILE_OFFSET_BITS=64)

project(crow-frame)
include_directories("./crow/include")
link_directories("/usr/local/lib")
link_libraries(PocoJWT PocoJSON PocoFoundation PocoData PocoDataPostgreSQL)
add_executable(${PROJECT_NAME} "main.cpp" "token.h" "token.cpp"
    "define.h" "public_function.h" "public_function.cpp" "database.h" "database.cpp"
    "service.h" "service.cpp" "controller.h" "controller.cpp" "response.h" "error_code.h" "error_code.cpp"
    "cors.h" "error_handler.h" "route.h")
