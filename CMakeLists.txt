cmake_minimum_required(VERSION 3.10)
project(c_homeworks C)

# Базовые настройки
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Добавляем дополнительные предупреждения (без флагов оптимизации)
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
    
    # 1. Находим все .c файлы в папке домашней работы
    file(GLOB ALL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/${HW_NAME}/*.c)
    
    if(NOT ALL_SOURCES)
        message(WARNING "No .c files found in src/${HW_NAME}/")
        return()
    endif()
    
    # Создаём основной исполняемый файл
    add_executable(${HW_NAME}
        ${ALL_SOURCES}
    )
    
    target_include_directories(${HW_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/${HW_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/${HW_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    message(STATUS "Added executable: ${HW_NAME}")
    
    # Проверяем наличие тестов
    set(TEST_SOURCES "")
    
    # Ищем тестовые файлы в tests/${HW_NAME}/
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/${HW_NAME}/)
        file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/${HW_NAME}/*.c)
        if(TEST_FILES)
            # Создаем статическую библиотеку из тестов (БЕЗ main!)
            set(TEST_LIB_NAME "${HW_NAME}_tests")
            add_library(${TEST_LIB_NAME} STATIC
                ${TEST_FILES}
            )
            
            target_include_directories(${TEST_LIB_NAME} PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/src/${HW_NAME}
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${CMAKE_CURRENT_SOURCE_DIR}/include/${HW_NAME}
                ${CMAKE_CURRENT_SOURCE_DIR}
            )
            
            # Линкуем основную программу с тестовой библиотекой
            target_link_libraries(${HW_NAME} PRIVATE ${TEST_LIB_NAME})
            
            # Создаём цель для запуска тестов через флаг --test
            set(TEST_TARGET_NAME "test${HW_NAME}")
            # Делаем первую букву заглавной для цели
            string(SUBSTRING "${TEST_TARGET_NAME}" 0 1 FIRST_CHAR)
            string(TOUPPER "${FIRST_CHAR}" FIRST_CHAR_UPPER)
            string(SUBSTRING "${TEST_TARGET_NAME}" 1 -1 REST)
            set(TEST_TARGET_NAME "${FIRST_CHAR_UPPER}${REST}")
            
            if(WIN32)
                set(TEST_EXEC_PATH "${CMAKE_BINARY_DIR}/${HW_NAME}.exe")
            else()
                set(TEST_EXEC_PATH "${CMAKE_BINARY_DIR}/${HW_NAME}")
            endif()
            
            add_custom_target(${TEST_TARGET_NAME}
                COMMAND ${TEST_EXEC_PATH} --test
                DEPENDS ${HW_NAME}
                COMMENT "Running tests for ${HW_NAME} with --test flag..."
            )
            message(STATUS "  Added test target: ${TEST_TARGET_NAME} (runs with --test flag)")
        endif()
    endif()
    
    # Создаём alias цель для простой сборки с camelCase
    set(BUILD_TARGET_NAME "build${HW_NAME}")
    # Делаем первую букву заглавной для цели
    string(SUBSTRING "${BUILD_TARGET_NAME}" 0 1 FIRST_CHAR)
    string(TOUPPER "${FIRST_CHAR}" FIRST_CHAR_UPPER)
    string(SUBSTRING "${BUILD_TARGET_NAME}" 1 -1 REST)
    set(BUILD_TARGET_NAME "${FIRST_CHAR_UPPER}${REST}")
    
    add_custom_target(${BUILD_TARGET_NAME}
        DEPENDS ${HW_NAME}
        COMMENT "Building ${HW_NAME}..."
    )
    message(STATUS "  Added build target: ${BUILD_TARGET_NAME} (camelCase)")
endfunction()

# Автоматически находим все домашние работы
message(STATUS "Looking for homeworks in src/...")
file(GLOB ALL_HW_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src "src/*")

# Разрешаем сборку конкретной домашки через цель
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

# Создаём общую цель
add_custom_target(all_homeworks
    DEPENDS ${HW_LIST}
    COMMENT "Building all homeworks..."
)

# Цель для запуска всех тестов (через --test флаг)
if(HW_LIST)
    # Создаем цель для запуска всех тестов
    set(TEST_ALL_COMMAND "")
    foreach(HW_NAME ${HW_LIST})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/${HW_NAME}/)
            file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/${HW_NAME}/*.c)
            if(TEST_FILES)
                if(WIN32)
                    list(APPEND TEST_ALL_COMMAND "${CMAKE_BINARY_DIR}/${HW_NAME}.exe --test")
                else()
                    list(APPEND TEST_ALL_COMMAND "${CMAKE_BINARY_DIR}/${HW_NAME} --test")
                endif()
            endif()
        endif()
    endforeach()
    
    if(TEST_ALL_COMMAND)
        # Создаем скрипт для запуска всех тестов
        set(TEST_ALL_SCRIPT "${CMAKE_BINARY_DIR}/run_all_tests.sh")
        if(WIN32)
            set(TEST_ALL_SCRIPT "${CMAKE_BINARY_DIR}/run_all_tests.bat")
        endif()
        
        # Создаем кастомную цель для запуска всех тестов
        add_custom_target(TestAll
            COMMAND ${CMAKE_COMMAND} -E echo "Running all tests..."
            COMMAND ${CMAKE_COMMAND} -E echo "========================================"
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/test_results
            COMMAND ${CMAKE_COMMAND} -E touch ${TEST_ALL_SCRIPT}
        )
        
        # Добавляем команды для каждого теста
        foreach(TEST_CMD ${TEST_ALL_COMMAND})
            get_filename_component(HW_NAME "${TEST_CMD}" NAME_WE)
            add_custom_command(TARGET TestAll
                COMMAND ${CMAKE_COMMAND} -E echo "Running tests for ${HW_NAME}..."
                COMMAND ${TEST_CMD} 2>&1 | tee ${CMAKE_BINARY_DIR}/test_results/${HW_NAME}.txt
                COMMAND ${CMAKE_COMMAND} -E echo "----------------------------------------"
            )
        endforeach()
        
        add_custom_command(TARGET TestAll
            COMMAND ${CMAKE_COMMAND} -E echo "All tests completed!"
            COMMAND ${CMAKE_COMMAND} -E echo "========================================"
        )
        
        message(STATUS "Added target 'TestAll' for running all tests with --test flag")
    else()
        message(STATUS "No tests found in any homework, skipping 'TestAll' target")
    endif()
endif()

if(NOT HW_LIST)
    message(WARNING "No homeworks found in src/ directory")
endif()