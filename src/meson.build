xper_c_sources = [
  'main.c',
  'xper_c-window.c',
]

xper_c_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

xper_c_sources += gnome.compile_resources('xper_c-resources',
  'xper_c.gresource.xml',
  c_name: 'xper_c'
)

executable('xper-c', xper_c_sources,
  dependencies: xper_c_deps,
  install: true,
)
