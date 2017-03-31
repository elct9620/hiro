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
  def initialize
    super

    use SpriteRenderer.new('examples/Misaki.png')
    use Animator.new(48, 56)
  end
end

class ExampleScene < Scene
  def initialize
    super

    @misaki = Misaki.new
    @misaki.animator
           .set(:idle, [*3..6])
           .set(:walk, [*25..30])
           .set(:run, [*13..20])
           .set(:jump_up, [*10..12])
           .set(:jump_fall, [*7..9])
           .set(:turn, [*21..24])
           .set(:blink, [*0..2])
    @misaki.animator.fps = 6
    @misaki.animator.to(:walk)
    add @misaki

    Event.on :keydown do |data|
      case data[:key]
      when Keyboard::LEFT then @misaki.x -= 5
      when Keyboard::RIGHT then @misaki.x += 5
      when Keyboard::UP then @misaki.animator.to(:jump_up, true).and_to(:jump_fall)
      end
    end
  end
end

Config.setup do
  title 'Example Game'
  default_scene ExampleScene
end

start ExampleGame
