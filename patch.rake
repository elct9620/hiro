require 'shellwords'

BASE_PATH = File.expand_path(File.dirname(__FILE__))

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

      def hiro(name, *arguments)
        name = "hiro-#{name}"
        arguments = arguments.last.kind_of?(Hash) ? arguments.pop : {}
        add_dependency(name, arguments.merge(path: File.join(BASE_PATH, name)))
      end
    end
  end
end
