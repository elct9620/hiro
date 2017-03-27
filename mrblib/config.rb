# Conifg
class Config
  def self.configs
    @configs ||= {}
  end

  def self.register(name, value)
    return if configs.key?(name.to_sym)
    set(name, value)
  end

  def self.set(name, value)
    name = name.to_s
    name = name[0..-2] if name[-1] == '='
    configs[name.to_sym] = value
  end

  def self.get(name)
    configs[name.to_sym]
  end

  def self.respond_to_missing?(name, include_private = false)
    super
  end

  def self.method_missing(name, *args, &block)
    return set(name, args.first) if name.to_s[-1] == '='
    return set(name, args.first) unless args.empty?
    return get(name) if configs.key?(name.to_sym)
    super
  end

  def self.setup(&block)
    class_eval(&block)
  end

  register :title, 'Hiro Framework'
  register :width, 1080
  register :height, 720
end
