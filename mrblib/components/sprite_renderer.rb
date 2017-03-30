# Component / Sprite Renderer
class SpriteRenderer < Component
  attr_accessor :width, :height

  def initialize(path, width = nil, height = nil)
    super()
    @path = path
    @width = width || 0
    @height = height || 0
    @scale = Vector2.new(1, 1)

    init
  end

  def parent
    game_object.parent
  end

  def x
    return game_object.x if parent.nil?
    game_object.x + parent.x
  end

  def y
    return game_object.y if parent.nil?
    game_object.y + parent.y
  end

  def scale
    return game_object.scale if parent.nil?
    game_object.scale * parent.scale
  end
end
