win = Window.new "Hiro Example"
renderer = Renderer.new win
sprite = Sprite.new renderer, "examples/gamepad.png", 100, 100

puts sprite.instance_variables

stop = false

Event.on Event::KEYDOWN do |data|
  stop = true if data.key == Keyboard::ESC
  case data.key
  when Keyboard::LEFT then sprite.x -= 10
  when Keyboard::RIGHT then sprite.x += 10
  when Keyboard::UP then sprite.y -= 10
  when Keyboard::DOWN then sprite.y += 10
  end
end

Event.on Event::QUIT do
  stop = true
end

while !stop
  Event.poll
  renderer.update do
    sprite.draw
  end
end
