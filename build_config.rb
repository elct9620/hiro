require File.join(File.expand_path(File.dirname(__FILE__)), 'patch')

MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gem 'hiro-exe'
end

