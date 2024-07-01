cmake_minimum_required(VERSION 3.20)

project(wxtest VERSION 1.2.0.1 LANGUAGES CXX)

set(BIN_NAME "${PROJECT_NAME}${PROJECT_VERSION_MAJOR}-${PROJECT_VERSION_MINOR}")

find_package(wxWidgets REQUIRED COMPONENTS xrc core base)
include(${wxWidgets_USE_FILE})

add_executable(${BIN_NAME})

add_subdirectory(src)

target_compile_definitions (${BIN_NAME} PRIVATE PROGRAM_NAME="${PROJECT_NAME} ${PROJECT_VERSION}" PROGRAM_DATADIR="${PROJECT_SOURCE_DIR}/data")
target_link_libraries(${BIN_NAME} PRIVATE ${wxWidgets_LIBRARIES})

add_custom_target(run
    COMMAND ${BIN_NAME}
    DEPENDS ${BIN_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)