class Sprite
  attr_reader :renderer

  def initialize(path, position = nil, width = 0, height = 0)
    @position = position || Vector2.new(0, 0)
    add_component RendererComponent.new(path, width, height)
  end
end
