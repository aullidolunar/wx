# locales

# generate pot:
find_program(XGETTEXT_EXECUTABLE xgettext REQUIRED)

set(POT_FILE "${PROJECT_SOURCE_DIR}/data/${BIN_NAME}.pot")

add_custom_command(
	OUTPUT "${POT_FILE}"
	COMMAND ${XGETTEXT_EXECUTABLE} --from-code="utf-8" --package-name=${PROJECT_NAME} --package-version=${PROJECT_VERSION} --msgid-bugs-address="aullidolunar@gmail.com" --copyright-holder="aullidolunar" -k_ --c++ --add-comments -o "${POT_FILE}" "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_custom_target(createpot DEPENDS "${POT_FILE}")

# generate po:
find_program(MSGINIT_EXECUTABLE msginit REQUIRED)

add_custom_target(createpo DEPENDS "${POT_FILE}"
	COMMAND ${MSGINIT_EXECUTABLE} -i ${POT_FILE} -l "es_MX.UTF-8" --no-translator -o "${PROJECT_SOURCE_DIR}/locales/es_MX.po"
)

# merge new pot with current po:
find_program(MSGMERGE_EXECUTABLE msgmerge REQUIRED)

add_custom_target(updatepo DEPENDS "${POT_FILE}" 
	COMMAND ${MSGMERGE_EXECUTABLE} -U --backup="off" "${PROJECT_SOURCE_DIR}/locales/es_MX.po" "${POT_FILE}"
)

# generate translations:
find_program(MSGFMT_EXECUTABLE msgfmt REQUIRED)

file(GLOB PO_FILES LIST_DIRECTORIES FALSE ${CMAKE_PROJECT_DIR} "*.po")

add_custom_target(translations ALL)

set(LOCALE_PREFIX "${CMAKE_BINARY_DIR}/locale")

foreach(PO_FILE ${PO_FILES})
	cmake_path(GET PO_FILE STEM PO_LOCALE)
	add_custom_command(
		TARGET translations
		DEPENDS "${CMAKE_PROJECT_DIR}/${PO_FILE}"
		COMMAND ${CMAKE_COMMAND} -E make_directory "${LOCALE_PREFIX}/${PO_LOCALE}"
		COMMAND ${MSGFMT_EXECUTABLE} ${PO_FILE} -o "${LOCALE_PREFIX}/${PO_LOCALE}/${BIN_NAME}.mo"
	)
endforeach()

add_dependencies(${BIN_NAME} translations)

target_compile_definitions (${BIN_NAME} PRIVATE USE_PROGRAM_CATALOG PROGRAM_CATALOG="${BIN_NAME}" PROGRAM_LOCALEDIR="${LOCALE_PREFIX}")