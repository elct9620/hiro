# Hiro Example
class ExampleGame < Game
  def initialize
    super
    Event.on :keydown do
      stop!
    end
  end
end

class GamePad < GameObject
  def initialize
    super

    use SpriteRenderer.new("examples/gamepad.png")
  end
end

class ExampleScene < Scene
  def initialize
    super

    @gamepad = GamePad.new
    add @gamepad
  end
end

Config.setup do
  title 'Example Game'
  default_scene ExampleScene
end

start ExampleGame
