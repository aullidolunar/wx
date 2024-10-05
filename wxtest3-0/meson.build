# .

# rsync -arvu --delete --delete-excluded --exclude=_build/ staged/ wxtestn-n/
# meson setup _build
# meson compile -C _build

# i18n:

# For add/remove languages, edit LINGUAS and then:
# meson setup _build --reconfigure
# Generate sources pot and po templates files with:
# meson compile -C _build wxtestx-update-po
# Edit po files as need it, then:
# meson compile -C _build [run]

project('wxtest', 'cpp', version : '3.0.0.0', default_options : ['cpp_std=c++14', 'warning_level=3'])

MAINTEINER_ENABLE = get_option('MAINTEINER_ENABLE')
IS_WIN            = (build_machine.system() == 'windows') ? true : false

FS       = import('fs')
zip_path = find_program('7z', required: false)

wx_dep          = dependency('wxwidgets', version : '>=3.1.0', modules : ['std', 'stc', 'xrc'], required: true)
PROGRAM_VERSION = meson.project_version()
version_token   = PROGRAM_VERSION.split('.')
PROGRAM_NAME    = '@0@@1@'.format(meson.project_name(), version_token[0])
PROGRAM_TITLE   = '@0@ v@1@'.format(PROGRAM_NAME, PROGRAM_VERSION)
PROGRAM_DESC    = 'wxWidgets application demo'
PROGRAM_DEFS    = [
  '-DPROGRAM_NAME="' + PROGRAM_NAME + '"',
  '-DPROGRAM_VERSION="' + PROGRAM_VERSION + '"',
  '-DPROGRAM_TITLE="' + PROGRAM_TITLE + '"'
]

if IS_WIN
  uname_executable = find_program('uname', required: false)
  if uname_executable.found()
    host_box = run_command(
      uname_executable,
	  '-o',
	  capture: true,
	  check: true
    ).stdout().strip()
    if host_box == 'Msys'
      PROGRAM_DEFS  += '-DWITH_MSYS2'
    endif
  endif
endif

PROGRAM_SOURCES  = []
I18N_SOURCES     = []
I18N_DEPS        = []
PROGRAM_INCDIRS  = []

subdir('scripts')
subdir('src')
subdir('data')
subdir('locale')

program_executable = executable(
  PROGRAM_NAME,
  PROGRAM_SOURCES,
  I18N_DEPS,
  dependencies: wx_dep,
  cpp_args: PROGRAM_DEFS,
  include_directories: PROGRAM_INCDIRS,
  native: true,
  export_dynamic: true
)

run_target(
  'run',
  command: [
    program_executable
  ]
)

if zip_path.found()
  project_dir = FS.parent(meson.project_build_root())
  run_target(
    'zip',
    command: [
      zip_path,
      'a',
      '-t7z',
      '-xr!*_build',
      f'@PROGRAM_NAME@-@PROGRAM_VERSION@-src.7z',
      project_dir
    ]
  )
endif