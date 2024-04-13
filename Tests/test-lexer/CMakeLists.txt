set(PROJECT_NAME test-lexer)
project(${PROJECT_NAME})

set(TESTS test-if-block.cpp test-strings.cpp)

add_executable(${PROJECT_NAME} ${TESTS} main.h main.cpp)