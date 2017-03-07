Config.setup do
 name  "Example Game"
end

class ExampleScene < Scene
  def initialize
    @keyframe = {
      down: [0, 1, 2],
      left: [3, 4, 5],
      right: [6, 7, 8],
      up: [9, 10, 11]
    }
    @counts = 0
    @animation = :down
    @sprite = Sprite.new "examples/gamepad.png", Vector2.new(100, 100)
    @sprite2 = Sprite.new "examples/character.png", Vector2.new(100, 100)

    @sprite.add @sprite2

    @sprite2.renderer.width = 32
    @sprite2.renderer.height = 32
    @sprite2.renderer.animate = true

    add @sprite

    # NOTE: Event manager seems can have more improve
    Event.on Event::KEYDOWN, &on_keydown
  end

  def on_keydown
    Proc.new { |data|
      case data.key
      when Keyboard::LEFT
        @sprite.x -= 5
        @animation = :left
      when Keyboard::RIGHT
        @sprite.x += 5
        @animation = :right
      when Keyboard::UP
        @sprite.y -= 5
        @animation = :up
      when Keyboard::DOWN
        @sprite.y += 5
        @animation = :down
      end

      @sprite2.renderer.frame = @keyframe[@animation][@counts]
      @counts = (@counts + 1) % 3
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
