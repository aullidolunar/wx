# src

target_sources(${BIN_NAME} PRIVATE main.cpp frame.cpp)

# generate locales:
find_program(XGETTEXT_EXECUTABLE xgettext REQUIRED)

set(POT_FILE "${PROJECT_SOURCE_DIR}/data/${BIN_NAME}.pot")
set(POT_FILE_EX "${CMAKE_PROJECT_DIR}/${BIN_NAME}_ex.pot")

add_custom_command(
	OUTPUT "${POT_FILE}"
	COMMAND ${XGETTEXT_EXECUTABLE} --from-code=utf-8 --package-name=${PROJECT_NAME} --package-version=${PROJECT_VERSION} --msgid-bugs-address="aullidolunar@gmail.com" --copyright-holder="aullidolunar" -k_ --c++ --add-comments -o "${POT_FILE}" "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_custom_target(createpot DEPENDS "${POT_FILE}")

find_program(MSGINIT_EXECUTABLE msginit REQUIRED)

add_custom_target(createpo DEPENDS "${POT_FILE}"
	COMMAND ${MSGINIT_EXECUTABLE} -i ${POT_FILE} -l es_MX.UTF-8 -o "${PROJECT_SOURCE_DIR}/locales/es_MX.po"
)
