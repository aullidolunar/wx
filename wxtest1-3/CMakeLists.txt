# .

cmake_minimum_required(VERSION 3.20)

project(wxtest VERSION 1.3.0.2 DESCRIPTION "Programa prueba de wxWidgets" LANGUAGES CXX)

set(BIN_NAME "${PROJECT_NAME}${PROJECT_VERSION_MAJOR}-${PROJECT_VERSION_MINOR}")

find_package(wxWidgets REQUIRED COMPONENTS xrc core base)
include(${wxWidgets_USE_FILE})

add_executable(${BIN_NAME})

add_subdirectory(src)
add_subdirectory(data)
add_subdirectory(locales)

target_compile_definitions (${BIN_NAME} PRIVATE PROGRAM_NAME="${PROJECT_NAME} ${PROJECT_VERSION}")
target_link_libraries(${BIN_NAME} PRIVATE ${wxWidgets_LIBRARIES})

add_custom_target(run
    COMMAND ${BIN_NAME}
    DEPENDS ${BIN_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)