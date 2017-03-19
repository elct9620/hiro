load File.join(File.expand_path(File.dirname(__FILE__)), '../patch.rake')

MRuby::Gem::Specification.new('hiro-core') do |spec|
  spec.license = 'Apache 2.0'
  spec.author  = ['Aotokitsuruya']
  spec.summary = 'The core parts of Hiro Framework'

  spec.search_package(:sdl2)
  spec.search_package(:SDL2_image)

  spec.add_dependency('mruby-compiler', core: 'mruby-compiler')
  spec.add_dependency('mruby-print', core: 'mruby-print')
  spec.add_dependency('mruby-object-ext', core: 'mruby-object-ext')
end
