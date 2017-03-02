class Config
  register :name, "Hiro Framework"
  register :width, 1080
  register :height, 720
  register :default_scene, Scene

  def self.setup(&block)
    @@instance.instance_exec(&block) if block_given?
  end

  def method_missing(name, *args, &block)
    # TODO: Add error fallback when Config not support
    Config.send(name, *args, &block)
  end
end
