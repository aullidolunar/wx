# locales

# generate translations:
find_program(MSGFMT_EXECUTABLE msgfmt REQUIRED)

file(GLOB PO_FILES LIST_DIRECTORIES FALSE ${CMAKE_PROJECT_DIR} "*.po")

add_custom_target(translations ALL)

foreach(PO_FILE ${PO_FILES})
	cmake_path(GET PO_FILE STEM PO_LOCALE)
	add_custom_command(
		TARGET translations
		DEPENDS "${CMAKE_PROJECT_DIR}/${PO_FILE}"
		COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/locales/${PO_LOCALE}"
		COMMAND ${MSGFMT_EXECUTABLE} ${PO_FILE} -o "${CMAKE_BINARY_DIR}/locales/${PO_LOCALE}/${BIN_NAME}.mo"
	)
endforeach()

add_dependencies(${BIN_NAME} translations)

target_compile_definitions (${BIN_NAME} PRIVATE PROGRAM_CATALOG="${BIN_NAME}" PROGRAM_LOCALEDIR="${CMAKE_BINARY_DIR}/locales")
