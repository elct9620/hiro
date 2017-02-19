win = Window.new "Hiro Example"
renderer = Renderer.new win

stop = false

Event.on Event::QUIT do
  puts "User closed game!"
  stop = true
end

while !stop
  Event.poll
  renderer.update
end
