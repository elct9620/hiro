Config.setup do
 name  "Example Game"
end

class ExampleScene < Scene
  def initialize
    @sprite = Sprite.new "examples/gamepad.png", Vector2.new(100, 100)

    add @sprite

    # NOTE: Event manager seems can have more improve
    Event.on Event::KEYDOWN, &on_keydown
  end

  def on_keydown
    Proc.new { |data|
      Hiro.quit! if data.key == Keyboard::ESC
      case data.key
      when Keyboard::LEFT then @sprite.x -= 10
      when Keyboard::RIGHT then @sprite.x += 10
      when Keyboard::UP then @sprite.y -= 10
      when Keyboard::DOWN then @sprite.y += 10
      end
    }
  end
end

class HiroGame < Game
  def initialize
    super

    @scene = ExampleScene.new
  end

  def update
    @scene.update
  end

  def draw
    @scene.draw
  end
end

Event.on Event::QUIT do
  Hiro.quit!
end

Hiro.entrypoint = HiroGame
