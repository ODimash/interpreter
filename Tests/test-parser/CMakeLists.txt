set(PROJECT_NAME test-parser)
project(${PROJECT_NAME})

set(TESTS "test-expression.cpp"  "test-parser.cpp")

add_executable(${PROJECT_NAME} ${TESTS} main.h main.cpp)