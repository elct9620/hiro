# Component / Sprite Renderer
class SpriteRenderer < Component
  def initialize(path, width = nil, height = nil)
    @path = path
    @width = width
    @height = height

    init
  end
end
