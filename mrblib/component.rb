# Component
class Component
  attr_reader :game_object

  def initialize
    @game_object = nil
  end

  def init; end

  def update(ticks); end

  def draw; end
end
