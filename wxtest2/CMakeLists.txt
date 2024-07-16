# .

cmake_minimum_required(VERSION 3.20)

project(wxtest VERSION 2.0.0.2 DESCRIPTION "Programa prueba de wxWidgets" LANGUAGES CXX)

set(BIN_NAME "${PROJECT_NAME}${PROJECT_VERSION_MAJOR}-${PROJECT_VERSION_MINOR}")

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(${BIN_NAME})

if (WIN32 AND MINGW)
	target_compile_definitions (${BIN_NAME} PRIVATE WITH_MSYS2)
endif()

add_subdirectory(src)
add_subdirectory(data)

target_compile_definitions (${BIN_NAME} PRIVATE PROGRAM_NAME="${PROJECT_NAME} ${PROJECT_VERSION}")
target_link_libraries(${BIN_NAME} PRIVATE ${wxWidgets_LIBRARIES})

add_custom_target(run
    COMMAND ${BIN_NAME}
    DEPENDS ${BIN_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH MY_PROJECT_DIR)
cmake_path(GET PROJECT_SOURCE_DIR STEM MY_PROJECT_NAME)

add_custom_target(dist
	WORKING_DIRECTORY "${MY_PROJECT_DIR}"
	COMMAND ${CMAKE_COMMAND} -E tar cvf "${CMAKE_CURRENT_BINARY_DIR}/${BIN_NAME}.7z" --format=7zip "${MY_PROJECT_NAME}/data" "${MY_PROJECT_NAME}/src" "${MY_PROJECT_NAME}/CMakeLists.txt"
)

