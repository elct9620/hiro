Config.setup do
 name  "Example Game"
end

class ExampleScene < Scene
  def initialize
    @sprite = Sprite.new "examples/gamepad.png", Vector2.new(100, 100)
    @sprite2 = Sprite.new "examples/gamepad.png", Vector2.new(50, 50)

    @object = GameObject.new
    @object.x = 100
    @object.y = 100
    @object.add_component RendererComponent.new("examples/gamepad.png")

    @sprite.add @sprite2
    @sprite.add @object

    add @sprite

    # NOTE: Event manager seems can have more improve
    Event.on Event::KEYDOWN, &on_keydown
  end

  def on_keydown
    Proc.new { |data|
      case data.key
      when Keyboard::LEFT then @sprite.x -= 10
      when Keyboard::RIGHT then @sprite.x += 10
      when Keyboard::UP then @sprite.y -= 10
      when Keyboard::DOWN then @sprite.y += 10
      end
    }
  end
end

# TODO: Support using string as scene class name
Config.default_scene ExampleScene

class HiroGame < Game
end

Event.on Event::QUIT do
  Hiro.quit!
end

Event.on Event::KEYDOWN do |data|
  Hiro.quit! if data.key == Keyboard::ESC
end

Hiro.entrypoint = HiroGame
