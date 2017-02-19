require 'common'

module Packager
  class Base
    def initialize(name: "Hiro", dest: BUILD_DIR)
      @name = name
      @dest = dest

      package
    end

    def exe_name
      @name
    end

    def identifier
      "tw.frost.Hiro"
    end

    def package
    end
  end
end
