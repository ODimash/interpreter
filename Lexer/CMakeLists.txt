
include_directories(include)
add_executable(Lexer "Lexer.cpp" "include/Lexer.h" "include/TokenTypes.h"  )

add_library(LexerLib STATIC
	Lexer.cpp
)

set_target_properties(Lexer PROPERTIES 
	OUTPUT_NAME "Lexer"
)

# ”казываем версию и местоположение дл€ установки
install(TARGETS Lexer
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)