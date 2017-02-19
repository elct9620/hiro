require 'erb'

require 'packager/base'

module Packager
  class OSX < Base
    TEMPLATE_FILE = File.expand_path(File.join("templates", "osx", "Info.plist.erb"))
    DYLIB_PATTERN = /(\/.+?\/opt.+?([A-Za-z0-9\-_\.]+\.dylib))/

    def package
      work_in(@dest) do
        setup_directory
        setup_app_info
        copy_binary
        replace_dylib
      end
    end

    def app_name
      "#{@name}.app"
    end

    def bundle_name
      @name
    end

    def binary_path
      "#{app_name}/Contents/MacOS/#{@name}"
    end

    private

    def setup_directory
      FileUtils.mkdir_p "#{app_name}/Contents/MacOS"
      FileUtils.mkdir_p "#{app_name}/Contents/Resources"
    end

    def setup_app_info
      context = binding
      File.write(
        "#{app_name}/Contents/Info.plist",
        ERB.new(File.read(TEMPLATE_FILE)).result(context)
      )
    end

    def copy_binary
      FileUtils.cp "hiro", binary_path
    end

    def replace_dylib
      dylibs = `otool -L #{binary_path}`.scan(DYLIB_PATTERN)
      dylibs.each do |origin, libname|
        `install_name_tool -change #{origin} ./#{libname} #{binary_path}`
        FileUtils.cp origin, "#{app_name}/Contents/MacOS"
      end
    end
  end
end
