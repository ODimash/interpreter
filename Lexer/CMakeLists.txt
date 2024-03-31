# Добавляем библиотеку Lexer
set(PROJECT_NAME Lexer)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME}
    Lexer.cpp
    # Добавьте сюда все другие cpp-файлы вашей библиотеки, если они есть
)

# Установите путь к заголовочным файлам для библиотеки
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Это необходимо, если у вас есть cpp файлы, которые используют std::string или другие стандартные типы
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
