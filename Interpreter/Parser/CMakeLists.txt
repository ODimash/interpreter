set(PROJECT_NAME Parser)
project(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC)

set(SOURCES
	"Expression.cpp"
	"BinaryExpression.cpp"
	"NumberExpression.cpp"
	"Parser.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Lexer)