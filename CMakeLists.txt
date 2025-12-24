cmake_minimum_required(VERSION 3.10)
project(c_homeworks C)

# Базовые настройки
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Добавляем дополнительные предупреждения (без флагов оптимизации)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Включаем CTest
include(CTest)

# Гарантируем, что тесты включены по умолчанию
if(NOT DEFINED BUILD_TESTING)
    set(BUILD_TESTING ON)
endif()

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
    
    # Сохраняем абсолютный путь к папке с домашкой для использования в include_directories
    set(HW_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/${HW_NAME})
    
    # 3. Ищем "главный" файл (по приоритету):
    #    - {HW_NAME}.c (mathOperations.c)
    #    - main.c
    #    - первый .c файл
    set(MAIN_SOURCE "")
    
    # Приоритет 1: файл с именем как папка
    foreach(source ${ALL_SOURCES})
        get_filename_component(FNAME_WE ${source} NAME_WE)
        if(FNAME_WE STREQUAL ${HW_NAME})
            set(MAIN_SOURCE ${source})
            message(STATUS "  Using ${HW_NAME}.c as main file")
            break()
        endif()
    endforeach()
    
    # Приоритет 2: main.c
    if(NOT MAIN_SOURCE)
        foreach(source ${ALL_SOURCES})
            get_filename_component(FNAME ${source} NAME)
            if(FNAME STREQUAL "main.c")
                set(MAIN_SOURCE ${source})
                message(STATUS "  Using main.c as main file")
                break()
            endif()
        endforeach()
    endif()
    
    # Приоритет 3: первый попавшийся .c файл
    if(NOT MAIN_SOURCE AND ALL_SOURCES)
        list(GET ALL_SOURCES 0 MAIN_SOURCE)
        get_filename_component(FNAME ${MAIN_SOURCE} NAME)
        message(STATUS "Using ${FNAME} as main file (first found)")
    endif()
    
    # 4. Создаём исполняемый файл
    if(MAIN_SOURCE)
        # Убираем MAIN_SOURCE из списка чтобы не дублировать
        list(REMOVE_ITEM ALL_SOURCES ${MAIN_SOURCE})
        
        add_executable(${HW_NAME}
            ${MAIN_SOURCE}
            ${ALL_SOURCES}  # Остальные файлы
        )
        
        # Поддерживаем относительные пути в include
        # Добавляем несколько возможных путей для include
        target_include_directories(${HW_NAME} PRIVATE
            ${HW_SOURCE_DIR}                     # Текущая папка с исходниками
            ${CMAKE_CURRENT_SOURCE_DIR}/include  # Глобальная папка include
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${HW_NAME}  # Локальная папка include
            ${CMAKE_CURRENT_SOURCE_DIR}          # Корень проекта
        )
        
        # Добавляем цель с именем домашней работы
        message(STATUS "Added executable: ${HW_NAME}")
        
        # 5. Добавляем тест в CTest (запуск с флагом --test)
        if(BUILD_TESTING)
            add_test(
                NAME ${HW_NAME}_test
                COMMAND ${HW_NAME} --test
            )
            message(STATUS "Added CTest target: ${HW_NAME}_test")
        endif()
        
        # 6. Также создаём цель для удобного запуска тестов
        add_custom_target(test_${HW_NAME}
            COMMAND ${HW_NAME} --test
            DEPENDS ${HW_NAME}
            COMMENT "Running tests for ${HW_NAME}..."
        )
        
        # Создаём alias цель для простой сборки
        add_custom_target(${HW_NAME}_build
            DEPENDS ${HW_NAME}
            COMMENT "Building ${HW_NAME}..."
        )
        
    else()
        message(WARNING "Could not determine main file for ${HW_NAME}")
    endif()
endfunction()

# Автоматически находим все домашние работы
message(STATUS "Looking for homeworks in src/...")
file(GLOB ALL_HW_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src "src/*")

# Разрешаем сборку конкретной домашки через цель
# Если передана переменная HW_TARGET, собираем только её
if(DEFINED HW_TARGET)
    message(STATUS "Building only target: ${HW_TARGET}")
    set(HW_LIST ${HW_TARGET})
elseif(DEFINED BUILD_HW)
    message(STATUS "Building only: ${BUILD_HW}")
    set(HW_LIST ${BUILD_HW})
else()
    # Берём все папки из src/
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

# Создаём общую цель для сборки всех домашек
add_custom_target(all_homeworks
    DEPENDS ${HW_LIST}
    COMMENT "Building all homeworks..."
)

# Добавляем цель для запуска всех тестов через CTest
if(HW_LIST AND BUILD_TESTING)
    add_custom_target(test_all
        COMMAND ctest --output-on-failure
        DEPENDS ${HW_LIST}
        COMMENT "Running all tests with CTest..."
    )
endif()

if(NOT HW_LIST)
    message(WARNING "No homeworks found in src/ directory")
    message(WARNING "Create folders like: src/mathOperations/, src/stringUtils/, etc.")
endif()