set(PROJECT_NAME Interpreter)
set(LEXER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../Lexer/include)
set(PARSER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../Parser/include)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} "Interpreter.cpp" "Interpreter.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# Добавляем путь к заголовочным файлам Lexer и Parser
#target_include_directories(${PROJECT_NAME} PUBLIC ${LEXER_INCLUDE} ${PARSER_INCLUDE})

# Связываем исполняемый файл с библиотекой Lexer
target_link_libraries(${PROJECT_NAME} PUBLIC Lexer)