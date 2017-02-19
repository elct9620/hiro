require 'packager/osx'

namespace :bundle do
  desc "Package OSX Application"
  task osx: :compile do
    Packager::OSX.new
  end
end
