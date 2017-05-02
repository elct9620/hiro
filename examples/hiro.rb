require 'misaki'
require 'scene'

# :nodoc:
class ExampleGame < Game
  def initialize
    super
    Event.on :keydown do |data|
      stop! if data[:key] == Keyboard::ESC
    end
  end
end

Config.setup do
  title 'Example Game'
  default_scene ExampleScene
end

start ExampleGame
