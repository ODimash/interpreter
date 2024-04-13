set(PROJECT_NAME Tests)
project(${PROJECT_NAME})

find_package(GTest MODULE REQUIRED)

add_subdirectory(test-lexer)
add_subdirectory(test-parser)

target_include_directories(test-lexer PRIVATE "../Interpreter/Lexer")
target_link_libraries(test-lexer GTest::GTest GTest::Main Lexer)

target_include_directories(test-parser PRIVATE "../Interpreter/Lexer" "../Interpreter/Parser")
target_link_libraries(test-parser GTest::GTest GTest::Main Lexer Parser)
