# Vector2
class Vector2
  # TODO: Implement compare detail
  include Comparable

  attr_accessor :x, :y

  def initialize(x = 0, y = 0)
    @x = x
    @y = y
  end

  def to_s
    "(#{@x}, #{@y})"
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
    return self unless %i(+ - * /).include?(method.to_sym)
    case other
    when Vector2 then x, y = operate_with_vec2(method, other)
    when Float, Integer then x, y = operate_with_number(method, other)
    else
      x = @x
      y = @y
    end
    Vector2.new(x, y)
  end

  def operate_with_vec2(method, other)
    [@x.send(method, other.x), @y.send(method, other.y)]
  end

  def operate_with_number(method, other)
    [@x.send(method, other), @y.send(method, other)]
  end
end
