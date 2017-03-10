class Vector2
  # TODO: Implement compare detail
  include Comparable

  attr_accessor :x, :y

  def initialize(x = 0, y = 0)
    @x = x
    @y = y
  end

  def +(other)
    operate(:+, other)
  end

  def -(other)
    operate(:-, other)
  end

  def *(other)
    operate(:*, other)
  end

  def /(other)
    operate(:/, other)
  end

  def operate(method, other)
    return self unless [:+, :-, :*, :/].include?(method.to_sym)
    case other
    when Vector2
      _x = @x.send(method, other.x)
      _y = @y.send(method, other.y)
    when Fixnum, Float, Integer
      _x = @x.send(method, other)
      _y = @y.send(method, other)
    else
      _x = 0
      _y = 0
    end
    Vector2.new(_x, _y)
  end
end
