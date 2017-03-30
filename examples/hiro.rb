# Hiro Example
class ExampleGame < Game
  def initialize
    super
    Event.on :keydown do |data|
      stop! if data[:key] == Keyboard::ESC
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
    @gamepad2 = GamePad.new
    @gamepad2.x = 100
    @gamepad.add @gamepad2
    add @gamepad

    Event.on :keydown do |data|
      case data[:key]
      when Keyboard::LEFT then @gamepad.x -= 5
      when Keyboard::RIGHT then @gamepad.x += 5
      end
    end
  end
end

Config.setup do
  title 'Example Game'
  default_scene ExampleScene
end

start ExampleGame
