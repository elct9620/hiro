MRuby::Gem::Specification.new('hiro') do |spec|
  spec.license = 'Apache 2.0'
  spec.author  = ['Aotokitsuruya']
  spec.summary = 'The 2D game framework based on mruby'

  search_package('sdl2')

  spec.bins = %w(hiro)

  spec.add_dependency('mruby-compiler', core: 'mruby-compiler')
  spec.add_dependency('mruby-print', core: 'mruby-print')
end
