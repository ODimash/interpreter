# CMakeList.txt: проект CMake для Interpreter; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Interpreter "Interpreter.cpp" "Interpreter.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Interpreter PROPERTY CXX_STANDARD 20)
endif()

include_directories( 
		${CMAKE_CURRENT_SOURCE_DIR}/../Lexer/include
		${CMAKE_CURRENT_SOURCE_DIR}/../Parser/include
)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.

target_link_libraries(Interpreter LexerLib)  # если нужно связать с библиотекой из Lexer
