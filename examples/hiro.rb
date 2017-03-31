# Hiro Example
class ExampleGame < Game
  def initialize
    super
    Event.on :keydown do |data|
      stop! if data[:key] == Keyboard::ESC
    end
  end
end

class Misaki < GameObject
  MAX_SPEED = 5

  def initialize
    super

    use SpriteRenderer.new('examples/Misaki.png')
    use Animator.new(48, 56)

    animator.set(:idle, [*3..6])
            .set(:walk, [*25..30])
            .set(:run, [*13..20])
            .set(:jump_up, [*10..12])
            .set(:jump_fall, [*7..9])
            .set(:turn, [*21..24])
            .set(:blink, [*0..2])
    animator.fps = 6
    animator.to(:walk)

    @speed = 0.5
    @velocity = 0
    @running = false
    @fixed_next_ticks = 1000 / 60
    @next_tick = 0
  end

  def update(ticks)
    return if @next_tick > ticks
    @next_tick = ticks + @fixed_next_ticks

    self.x += @velocity.to_i
    slow_down unless @running
    animator.to(pick_animation) if animator.current != pick_animation
  end

  def slow_down
    return unless @velocity != 0
    sign = @velocity.abs / @velocity
    scale = (@velocity.abs / 20).round(2)
    scale = 1 if scale < 1

    @velocity -= sign * scale
  end

  def pick_animation
    return :idle unless @velocity != 0
    return :run if @velocity.abs > 1.5
    :walk
  end

  def right
    @scale.x = 1
    @running = true
    @velocity += @speed
    @velocity = MAX_SPEED if @velocity >= MAX_SPEED
  end

  def left
    @scale.x = -1
    @running = true
    @velocity -= @speed
    @velocity = -MAX_SPEED if @velocity <= -MAX_SPEED
  end

  def stop
    @running = false
  end
end

class ExampleScene < Scene
  def initialize
    super

    @misaki = Misaki.new
    @misaki.y = 100
    @misaki.x = 100
    add @misaki

    Event.on :keydown do |data|
      case data[:key]
      when Keyboard::LEFT then @misaki.left
      when Keyboard::RIGHT then @misaki.right
      end
    end

    Event.on :keyup do |data|
      @misaki.stop
    end
  end
end

Config.setup do
  title 'Example Game'
  default_scene ExampleScene
end

start ExampleGame
