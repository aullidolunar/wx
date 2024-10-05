# src

mesonhelper_h = configure_file(
  input: files('MesonHelper.h.in'),
  output: '@BASENAME@',
  configuration: {
    'PROGRAM_DESC': PROGRAM_DESC
  }
)

sources = files('main.cpp', 'MyFrame.cpp')

PROGRAM_SOURCES += sources

sources += mesonhelper_h

foreach src: sources
	I18N_SOURCES += FS.relative_to(src, meson.project_source_root())
endforeach

PROGRAM_INCDIRS += include_directories('.')