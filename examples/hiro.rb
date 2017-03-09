Config.setup do
 name  "Example Game"
end

class ExampleScene < Scene
  def initialize
    @sprite = Sprite.new "examples/gamepad.png", Vector2.new(100, 100)
    @char = Animation.new "examples/Misaki.png", 48, 56, Vector2.new(100, 100)

    @sprite.add @char

    @char.animator.fps = 6
    @char.animator.set(:idle, [0, 1, 2, 3])
                  .set(:walk, [4, 9, 14, 15, 16, 17])
                  .set(:run, [5, 6, 7, 8, 10, 11, 12, 13])

    add @sprite

    @acc = 0

    # NOTE: Event manager seems can have more improve
    Event.on Event::KEYDOWN, &on_keydown
    Event.on Event::KEYUP, &on_keyup
  end

  def on_keyup
    Proc.new { |data|
      @char.animator.to(:idle)
      @acc = 0
    }
  end

  def on_keydown
    Proc.new { |data|
      @char.animator.play
      @acc += 1

      animation = @acc > 3 ? :run : :walk
      animate_switch = @char.animator.current != animation

      case data.key
      when Keyboard::LEFT
        # TODO: Add flip sprite support
        @sprite.x -= 10
        @char.animator.to(animation) if animate_switch
      when Keyboard::RIGHT
        @sprite.x += 10
        @char.animator.to(animation) if animate_switch
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
