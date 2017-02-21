class Vector2
  # TODO: Implement compare detial
  include Comparable

  attr_accessor :x, :y

  def initialize(x = 0, y = 0)
    @x = x
    @y = y
  end

  def +(other)
    return Vector2.new(@x + other.x, @y + other.y) if other.is_a?(Vector2)
    self
  end

  def -(other)
    return Vector2.new(@x - other.x, @y - other.y) if other.is_a?(Vector2)
    self
  end

  def *(other)
    return Vector2.new(@x * other.x, @y * other.y) if other.is_a?(Vector2)
    self
  end

  def /(other)
    return Vector2.new(@x / other.x, @y / other.y) if other.is_a?(Vector2)
    self
  end
end
