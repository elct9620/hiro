# Hiro Example
class ExampleGame < Game
  def initialize
    super
    Event.on :keydown do
      stop!
    end
  end
end

class ExampleScene < Scene
end

Config.setup do
  title 'Example Game'
  default_scene ExampleScene
end

start ExampleGame
