# Game Object
class GameObject
  attr_accessor :position

  def initialize
    @parent = nil
    @children = []
    @components = []
    @position = Vector2.new(0, 0)
  end

  def add(child)
    return unless child.is_a?(GameObject)
    @children.push(child)
  end

  def component(component)
    return unless component.is_a?(Component)
    @components.push(component)
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
end
