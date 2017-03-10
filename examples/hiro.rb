Config.setup do
 name  "Example Game"
end

class ExampleScene < Scene
  def initialize
    @sprite = Sprite.new "examples/gamepad.png", Vector2.new(100, 100)
    @char = Animation.new "examples/Misaki.png", 48, 56, Vector2.new(100, 100)

    @sprite.add @char

    @char.animator.fps = 6
    @char.animator.set(:idle, [*3..6])
                  .set(:walk, [*25..30])
                  .set(:run, [*13..20])
                  .set(:jump_up, [*10..12])
                  .set(:jump_fall, [*7..9])
                  .set(:turn, [*21..24])
                  .set(:blink, [*0..2])

    add @sprite

    @acc = 0
    @in_air = false
    @to_down = false
    @down_ticks = 0
    @last_ticks = 0
    @up_start = 0

    # NOTE: Event manager seems can have more improve
    Event.on Event::KEYDOWN, &on_keydown
    Event.on Event::KEYUP, &on_keyup
  end

  def update(ticks)
    # TODO: Implement Animation State Machine
    @down_ticks = @last_ticks + (1000 / 6)
    if @in_air
      @sprite.y -= 3
      @char.animator.to(:jump_up) if @char.animator.current != :jump_up
      if @char.animator.frame >= 2
        @in_air = false
        @to_down = true
        @sprite.y += 10
      end
    end

    if @to_down
      @char.animator.to(:jump_fall) if @char.animator.current == :jump_up
      if @char.animator.frame >= 2
        @to_down = false
        @char.animator.to(:idle)
      end
    end

    if @sprite.y != @up_start && !@in_air
      @sprite.y += 3
      @sprite.y = @up_start if @sprite.y > @up_start
    end
    @last_ticks = ticks
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
      when Keyboard::UP
        unless @in_air || @to_down
          @in_air = true
          @up_start = @sprite.y
        end
      when Keyboard::LEFT
        # TODO: Add flip sprite support
        @sprite.x -= 10
        @char.renderer.scale.x = -1
        @char.animator.to(animation) if animate_switch
      when Keyboard::RIGHT
        @char.renderer.scale.x = 1
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
