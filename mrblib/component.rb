# Component
class Component
  attr_reader :game_object

  def initialize
    @game_object = nil
  end

  def name
    self.class.to_s.underscore.to_sym
  end

  def init; end

  def update(ticks); end

  def draw; end

  def parent
    game_object.parent
  end
end
