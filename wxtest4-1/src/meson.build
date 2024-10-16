# src

sources = files('main.cpp', 'MyFrame.cpp')

PROGRAM_SOURCES += sources

foreach src: sources
	I18N_SOURCES += FS.relative_to(src, meson.project_source_root())
endforeach

PROGRAM_INCDIRS += include_directories('.')