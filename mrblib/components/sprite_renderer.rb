# Component / Sprite Renderer
class SpriteRenderer < Component
  attr_accessor :width, :height, :clip, :bound

  def initialize(path, width = nil, height = nil)
    super()
    @path = path
    @width = width || 0
    @height = height || 0
    @clip = false
    @bound = Rectangle.new(0, 0, 0, 0)

    init
  end

  def x
    return game_object.x if parent.nil?
    game_object.x + parent.x
  end

  def y
    return game_object.y if parent.nil?
    game_object.y + parent.y
  end

  def name
    :renderer
  end

  def scale
    return game_object.scale if parent.nil?
    game_object.scale * parent.scale
  end

  def clip?
    @clip
  end
end
