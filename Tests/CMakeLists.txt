set(PROJECT_NAME Tests)
project(${PROJECT_NAME})

find_package(GTest MODULE REQUIRED)

add_executable(test-lexer "test-lexer/test-if-block.cpp" "test-lexer/main.cpp" "test-lexer/test-strings.cpp" "test-lexer/main.h")
target_include_directories(test-lexer PRIVATE "../Interpreter/Lexer")
target_link_libraries(test-lexer GTest::GTest GTest::Main Lexer)
