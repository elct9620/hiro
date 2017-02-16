MRUBY_CONFIG=File.expand_path(ENV["MRUBY_CONFIG"] || "build_config.rb")

MRUBY_DIR = File.expand_path("deps/mruby")
BUILD_DIR = File.expand_path("build")

def work_in(target)
  current = Dir.pwd
  Dir.chdir target
  yield if block_given?
  Dir.chdir current
end

def clear_build
  FileUtils.rm_r(BUILD_DIR, force: true)
end

task :dependencies do
  sh "git submodule update --init --recursive"
end

desc "Compile binary"
task compile: :dependencies do
  clear_build

  work_in(MRUBY_DIR) do
    sh "MRUBY_CONFIG=#{MRUBY_CONFIG} rake all"
  end

  FileUtils.mkdir_p BUILD_DIR
  FileUtils.cp "#{MRUBY_DIR}/build/host/bin/hiro", BUILD_DIR
end

desc "Run compiled binary"
task run: :compile do
  sh "#{BUILD_DIR}/hiro"
end

desc "Clear compiled file"
  task :clean do
    clear_build
  end

namespace :clean do
  desc "Clear all compiled files"
  task :all do
    clear_build
    work_in MRUBY_DIR do
      sh "rake clean"
    end
  end
end
