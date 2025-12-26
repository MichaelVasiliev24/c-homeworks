cmake_minimum_required(VERSION 3.10)
project(c_homeworks C)

# Базовые настройки
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Добавляем дополнительные предупреждения
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Устанавливаем общую выходную директорию для всех исполняемых файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Создаём цель для конкретной домашней работы
function(add_homework HW_NAME)
    # Проверяем существование папки с домашкой
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/${HW_NAME})
        message(WARNING "Homework ${HW_NAME} not found in src/")
        return()
    endif()
    
    # Находим все .c файлы в папке домашней работы
    file(GLOB ALL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/${HW_NAME}/*.c)
    
    if(NOT ALL_SOURCES)
        message(WARNING "No .c files found in src/${HW_NAME}/")
        return()
    endif()
    
    # Создаём основной исполняемый файл
    add_executable(${HW_NAME}
        ${ALL_SOURCES}
    )
    
    # ВАЖНО: Добавляем пути к заголовочным файлам
    # 1. Общая include директория (для #include "optimalSorting/mergeSort.h")
    # 2. Конкретная подпапка (на случай если заголовки лежат прямо в include/)
    target_include_directories(${HW_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/${HW_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/${HW_NAME}
    )
    
    message(STATUS "Added executable: ${HW_NAME}")
    
    # Проверяем наличие тестов
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/${HW_NAME}/)
        file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/${HW_NAME}/*.c)
        if(TEST_FILES)
            # Создаем статическую библиотеку из тестов (БЕЗ main!)
            set(TEST_LIB_NAME "${HW_NAME}_tests")
            add_library(${TEST_LIB_NAME} STATIC
                ${TEST_FILES}
            )
            
            # Те же пути для тестов
            target_include_directories(${TEST_LIB_NAME} PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${CMAKE_CURRENT_SOURCE_DIR}/include/${HW_NAME}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/${HW_NAME}
            )
            
            # Линкуем основную программу с тестовой библиотекой
            target_link_libraries(${HW_NAME} PRIVATE ${TEST_LIB_NAME})
            
            # Создаём цель для запуска тестов через флаг --test
            if(WIN32)
                set(TEST_EXEC_PATH "${CMAKE_BINARY_DIR}/${HW_NAME}.exe")
            else()
                set(TEST_EXEC_PATH "${CMAKE_BINARY_DIR}/${HW_NAME}")
            endif()
            
            add_custom_target(test_${HW_NAME}
                COMMAND ${TEST_EXEC_PATH} --test
                DEPENDS ${HW_NAME}
                COMMENT "Running tests for ${HW_NAME} with --test flag..."
            )
            message(STATUS "  Added test target: test_${HW_NAME}")
        endif()
    endif()
endfunction()

# Автоматически находим все домашние работы
message(STATUS "Looking for homeworks in src/...")
file(GLOB ALL_HW_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src "src/*")

# Разрешаем сборку конкретной домашки через переменные
if(DEFINED HW_TARGET)
    message(STATUS "Building only target: ${HW_TARGET}")
    set(HW_LIST ${HW_TARGET})
elseif(DEFINED BUILD_HW)
    message(STATUS "Building only: ${BUILD_HW}")
    set(HW_LIST ${BUILD_HW})
else()
    set(HW_LIST "")
    foreach(HW_DIR ${ALL_HW_DIRS})
        get_filename_component(HW_NAME ${HW_DIR} NAME)
        if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/${HW_NAME})
            list(APPEND HW_LIST ${HW_NAME})
        endif()
    endforeach()
endif()

# Добавляем каждую домашку
foreach(HW_NAME ${HW_LIST})
    add_homework(${HW_NAME})
endforeach()

# Цель для запуска всех тестов (через --test флаг)
set(TEST_TARGETS "")
foreach(HW_NAME ${HW_LIST})
    if(TARGET test_${HW_NAME})
        list(APPEND TEST_TARGETS test_${HW_NAME})
    endif()
endforeach()

if(TEST_TARGETS)
    add_custom_target(test_all
        DEPENDS ${TEST_TARGETS}
        COMMENT "Running all tests..."
    )
    message(STATUS "Added target 'test_all' for running all tests")
endif()

if(NOT HW_LIST)
    message(WARNING "No homeworks found in src/ directory")
endif()