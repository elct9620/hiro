Config.setup do
 name  "Example Game"
end

class ExampleScene < Scene
  def initialize
    @sprite = Sprite.new "examples/gamepad.png", Vector2.new(100, 100)
    @char = Animation.new "examples/character.png", 32, 32, Vector2.new(100, 100)

    @sprite.add @char

    @char.animator.fps = 6
    @char.animator.set(:down, [0, 1, 2])
                  .set(:left, [3, 4, 5])
                  .set(:right, [6, 7, 8])
                  .set(:up, [9, 10, 11])
                  .stop


    add @sprite

    # NOTE: Event manager seems can have more improve
    Event.on Event::KEYDOWN, &on_keydown
    Event.on Event::KEYUP, &on_keyup
  end

  def on_keyup
    Proc.new { |data|
      @char.animator.stop
    }
  end

  def on_keydown
    Proc.new { |data|
      @char.animator.play

      case data.key
      when Keyboard::LEFT
        @sprite.x -= 5
        @char.animator.to(:left) unless data.repeat
      when Keyboard::RIGHT
        @sprite.x += 5
        @char.animator.to(:right) unless data.repeat
      when Keyboard::UP
        @sprite.y -= 5
        @char.animator.to(:up) unless data.repeat
      when Keyboard::DOWN
        @sprite.y += 5
        @char.animator.to(:down) unless data.repeat
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
