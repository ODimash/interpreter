set(PROJECT_NAME Lexer)
project(${PROJECT_NAME})

add_library(${PROJECT_NAME} Lexer.cpp)

add_executable(${PROJECT_NAME}_test Test.cpp Lexer.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(${PROJECT_NAME}_test PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Это необходимо, если у вас есть cpp файлы, которые используют std::string или другие стандартные типы
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
