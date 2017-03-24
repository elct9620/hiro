MRuby::Gem::Specification.new('hiro') do |spec|
  spec.license = 'Apache 2.0'
  spec.author  = ['Aotokitsuruya']
  spec.summary = 'The 2D game framework based on mruby'

  spec.search_package(:sdl2)
  spec.search_package(:SDL2_image)

  spec.bins = %w(hiro)

  spec.add_dependency('mruby-compiler', core: 'mruby-compiler')
  spec.add_dependency('mruby-print', core: 'mruby-print')
  spec.add_dependency('mruby-object-ext', core: 'mruby-object-ext')

  spec.hiro(:core)
end
