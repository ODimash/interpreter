set(PROJECT_NAME Interpreter)
set(LEXER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/include)
set(PARSER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Parser/include)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} "Interpreter.cpp" "Interpreter.h")
add_subdirectory(Lexer)
add_subdirectory(Parser)

# Добавляем путь к заголовочным файлам Lexer и Parser
target_include_directories(${PROJECT_NAME} PRIVATE ${LEXER_INCLUDE}
	${PARSER_INCLUDE})

# Связываем исполняемый файл с библиотекой Lexer
target_link_libraries(${PROJECT_NAME} PRIVATE Lexer)
