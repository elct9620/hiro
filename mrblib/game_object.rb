# Game Object
class GameObject
  attr_accessor :position
  attr_reader :parent

  def initialize
    @parent = nil
    @children = []
    @components = {}
    @position = Vector2.new(0, 0)
  end

  def x
    @position.x
  end

  def x=(x)
    @position.x = x
  end

  def y
    @position.y
  end

  def y=(y)
    @position.y = y
  end

  def update(ticks); end

  def draw; end

  def respond_to_missing?(name)
    super
  end

  def method_missing(name, *args, &block)
    return @components[name] if @components.has_key?(name)
    super
  end
end
