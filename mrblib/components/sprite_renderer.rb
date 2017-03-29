# Component / Sprite Renderer
class SpriteRenderer < Component
  def initialize(path, width = nil, height = nil)
    @path = path
    @width = width
    @height = height

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
end
