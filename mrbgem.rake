require 'shellwords'

# Patch for `mruby-1.2.0` to support third-party library
module MRuby
  module Gem
    class Specification
      def search_package(name, version_query=nil)
        package_query = name
        package_query += " #{version_query}" if version_query
        _pp "PKG-CONFIG", package_query
        escaped_package_query = Shellwords.escape(package_query)
        if system("pkg-config --exists #{escaped_package_query}")
          cc.flags += [`pkg-config --cflags #{escaped_package_query}`.strip]
          cxx.flags += [`pkg-config --cflags #{escaped_package_query}`.strip]
          linker.flags_before_libraries += [`pkg-config --libs #{escaped_package_query}`.strip]
          true
        else
          false
        end
      end
    end
  end
end

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
end
