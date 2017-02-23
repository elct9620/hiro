class HiroGame < Game
  def initialize
    super
    @sprite = Sprite.new "examples/gamepad.png", Vector2.new(100, 100)

    Event.on Event::KEYDOWN do |data|
      Hiro.quit! if data.key == Keyboard::ESC
      # TODO: Implement event manager
      case data.key
      when Keyboard::LEFT then @sprite.x -= 10
      when Keyboard::RIGHT then @sprite.x += 10
      when Keyboard::UP then @sprite.y -= 10
      when Keyboard::DOWN then @sprite.y += 10
      end
    end
  end

  def update
    @sprite.draw
  end
end

Event.on Event::QUIT do
  Hiro.quit!
end

Hiro.entrypoint = HiroGame
