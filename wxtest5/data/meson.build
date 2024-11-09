# data

wxrc_executable = find_program('wxrc', required: true)

xrc_file = files('MyFrame.xrc')

xrc_file_h = custom_target(
  input: xrc_file,
  output: '@PLAINNAME@.h',
  command: [
    wxrc_executable,
    '-c',
    '-g',
    '-o',
    '@OUTPUT@',
    '@INPUT@'
  ]
)

xrc_filename = FS.name(xrc_file)

PROGRAM_DATADIR = MAINTEINER_ENABLE ? meson.current_source_dir() : '.'
XRC_FILE        = PROGRAM_DATADIR / xrc_filename
PROGRAM_DEFS   += [
  f'-DXRC_FILE="@XRC_FILE@"',
  f'-DPROGRAM_DATADIR="@PROGRAM_DATADIR@"'
]

DESKTOP_FILE_IN = configure_file(
  input: 'desktop.in.in',
  output: PROGRAM_NAME + '.@BASENAME@',
  configuration: {
    'PROGRAM_NAME': PROGRAM_NAME,
    'PROGRAM_DESC': PROGRAM_DESC,
    'PROGRAM_ICON': meson.current_source_dir() / 'tux-logo-24.png'
  }
)

I18N_SOURCES += [
  FS.relative_to(DESKTOP_FILE_IN, meson.project_source_root()),
  FS.relative_to(xrc_file_h, meson.project_source_root()),
]

if IS_WIN
  windows = import('windows')
  resource = configure_file(
    input: files('resource.rc.in'),
    output: '@BASENAME@',
    configuration: {
      'PROGRAM_VERSION': PROGRAM_VERSION,
      'PROGRAM_VERSION_COMMA': PROGRAM_VERSION.replace('.', ','),
      'BIN_NAME': PROGRAM_NAME, 
      'PROGRAM_DESCRIPTION': PROGRAM_DESC
    }
  )
  PROGRAM_SOURCES += windows.compile_resources(
    resource,
    include_directories: meson.current_source_dir()
  )
endif
