class GameObject
  attr_accessor :position

  def x
    # TODO: Set default position
    @position ||= Vector2.new(0, 0)
    return @parent.x + @position.x if @parent
    @position.x
  end

  def x=(x)
    @position ||= Vector2.new(0, 0)
    @position.x = x
  end

  def y
    @position ||= Vector2.new(0, 0)
    return @parent.y + @position.y if @parent
    @position.y
  end

  def y=(y)
    @position ||= Vector2.new(0, 0)
    @position.y = y
  end
end
