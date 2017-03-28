# Game
class Game
  attr_accessor :current_scene

  def initialize
    @current_scene = nil

    init
  end

  def update(ticks); end

  def draw; end
end
