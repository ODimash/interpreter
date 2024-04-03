set(PROJECT_NAME Tests)
project(${PROJECT_NAME})
find_package(GTest MODULE REQUIRED)

add_subdirectory("test-lexer")
add_subdirectory("test-parser")

