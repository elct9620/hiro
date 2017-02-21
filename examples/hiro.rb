win = Window.new "Hiro Example"
renderer = Renderer.new win

stop = false

Event.on Event::KEYDOWN do |data|
  stop = true if data.key == Keyboard::ESC
end

Event.on Event::QUIT do
  stop = true
end

while !stop
  Event.poll
  renderer.update do
    # TODO: Puts Sprite drawer at here
  end
end
