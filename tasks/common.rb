def work_in(target)
  current = Dir.pwd
  Dir.chdir target
  yield if block_given?
  Dir.chdir current
end

def clear_build
  FileUtils.rm_r(BUILD_DIR, force: true)
end

