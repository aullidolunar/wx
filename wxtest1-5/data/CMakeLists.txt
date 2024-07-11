# data

function(DO_RC)
	set(RESOURCE_RC "${CMAKE_BINARY_DIR}/resource.rc")
	string(REPLACE "." "," PROJECT_VERSION_COMMA ${PROJECT_VERSION})
	configure_file("resource.rc.in" "${RESOURCE_RC}")
	target_sources(${BIN_NAME} PRIVATE "${RESOURCE_RC}")
endfunction()

if(WIN32)
	do_rc()
endif()

target_include_directories(${BIN_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${BIN_NAME} PRIVATE PROGRAM_DATADIR="${PROJECT_SOURCE_DIR}/data")
