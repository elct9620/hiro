# Game Object
class GameObject
  def initialize
    @children = []
    @components = []
  end

  def add(child)
    return unless child.is_a?(GameObject)
    @children.push(child)
  end

  def component(component)
    return unless component.is_a?(Component)
    @components.push(component)
  end

  def update(ticks); end

  def draw; end
end
