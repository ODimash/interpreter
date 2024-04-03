set(PROJECT_NAME Lexer)
project(${PROJECT_NAME})

add_library(${PROJECT_NAME} Lexer.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
