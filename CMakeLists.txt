cmake_minimum_required(VERSION 3.10)
project(ArrayLibrary)

# Использование стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Флаги для покрытия кода
set(COVERAGE_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_FLAGS}")

# Указание директории для заголовочных файлов
include_directories(include)

# Сбор всех исходных файлов
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Основной исполняемый файл (опционально, если есть main.cpp)
add_executable(main ${SRC_FILES})

# Добавление тестов
enable_testing()
add_subdirectory(tests)

# Цель для покрытия кода (опционально)
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

message(STATUS "LCOV_PATH: ${LCOV_PATH}")
message(STATUS "GENHTML_PATH: ${GENHTML_PATH}")

if(LCOV_PATH AND GENHTML_PATH)
    message(STATUS "LCOV и GENHTML найдены, добавляю цель coverage")

    add_custom_target(coverage
    COMMAND lcov --directory . --capture --output-file coverage.info --ignore-errors mismatch
    COMMAND lcov --remove coverage.info '/usr/*' '*/tests/*' --output-file coverage_filtered.info
    COMMAND genhtml coverage_filtered.info --output-directory coverage_report
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Генерация HTML отчёта покрытия кода"
    )
else()
    message(WARNING "LCOV или GENHTML не найдены, цель coverage не будет создана")
endif()
