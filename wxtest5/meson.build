# .

# rsync -arvu --delete --delete-excluded --exclude=build/ unzipped/ wxtest5/

# meson setup build [--reconfigure]
# meson compile -C build [run]

# i18n:
# to add/remove langs:
# edit LINGUAS as need it, then:
# meson setup build --reconfigure
# regenerate POTFILES with sources files:
# meson compile -C build potfiles
# extract strings from sources:
# meson compile -C build wxtest5-update-po
# edit po files as need it, then build:
# meson compile -C build

project('wxtest', 'cpp', version: '5.0.0.0', meson_version: '>= 1.5.0', default_options: ['cpp_std=c++11', 'warning_level=3'])

MAINTEINER_ENABLE = get_option('MAINTEINER_ENABLE')
IS_WIN = (build_machine.system() == 'windows') ? true : false

touch_bin = find_program('touch', required: false)
if touch_bin.found()
  TOUCH_CMD = touch_bin
  SH_CMD = ['sh', '-c']
else
  TOUCH_CMD = 'echo. >'
  SH_CMD = ['cmd', '/C']
endif

FS       = import('fs')

wx_dep          = dependency('wxwidgets', version: '>=3.1.0', modules: ['std', 'stc'], required: true)
jsoncpp_dep     = dependency('jsoncpp', required: true)

PROGRAM_VERSION = meson.project_version()
version_token   = PROGRAM_VERSION.split('.')
PROGRAM_NAME    = '@0@@1@'.format(meson.project_name(), version_token[0])
PROGRAM_DESC    = 'wxWidgets application demo'
PROGRAM_DEFS    = [
  f'-DPROGRAM_NAME="@PROGRAM_NAME@"',
  f'-DPROGRAM_VERSION="@PROGRAM_VERSION@"',
  f'-DPROGRAM_DESC="@PROGRAM_DESC@"'
]

prefix = get_option('prefix')

if IS_WIN and touch_bin.found()
  PROGRAM_DEFS  += [
    '-DWITH_MSYS2',
    f'-DPROGRAM_PREFIX="@prefix@"'
  ]
endif

message('prefix: ' + prefix)

PROGRAM_INCDIRS  = []
PROGRAM_SOURCES  = []
I18N_SOURCES     = []
I18N_DEPS        = []

sources = files('main.cpp', 'MyFrame.cpp', 'DialogItemEditor.cpp')
foreach src: sources
  I18N_SOURCES += FS.relative_to(src, meson.project_source_root())
endforeach

PROGRAM_SOURCES += sources

subdir('data')
subdir('locale')

program_executable = executable(
  PROGRAM_NAME,
  PROGRAM_SOURCES,
  I18N_DEPS,
  dependencies: [wx_dep, jsoncpp_dep],
  cpp_args: PROGRAM_DEFS,
  include_directories: PROGRAM_INCDIRS,
  native: true
)

run_target('run', command: [program_executable])

zip_path = find_program('7z', required: false)

if zip_path.found()
  project_dir = FS.parent(meson.project_build_root())
  build_dir = FS.name(meson.current_build_dir())
  run_target(
    'zip',
    command: [
      zip_path,
      'a',
      '-t7z',
      '-xr!@0@'.format(build_dir),
      f'@PROGRAM_NAME@-@PROGRAM_VERSION@-src.7z',
      project_dir
    ]
  )
endif
