class Animation < Sprite
  attr_reader :animator

  def initialize(path, width = 0, height = 0, position = nil)
    super path, position, width, height
    add_component AnimatorComponent.new

    @renderer.animate = true
  end

end
