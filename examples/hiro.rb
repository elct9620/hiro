game = Game.new
win = Window.new "Hiro Example"
renderer = Renderer.new win
sprite = Sprite.new renderer, "examples/gamepad.png", Vector2.new(100, 100)

Event.on Event::KEYDOWN do |data|
  game.stop! if data.key == Keyboard::ESC
  case data.key
  when Keyboard::LEFT then sprite.x -= 10
  when Keyboard::RIGHT then sprite.x += 10
  when Keyboard::UP then sprite.y -= 10
  when Keyboard::DOWN then sprite.y += 10
  end
end

Event.on Event::QUIT do
  game.stop!
end

game.loop do
  renderer.update do
    sprite.draw
  end
end
