Config.setup do
  title 'Example Game'
end

class ExampleGame < Game
  def initialize
    super
    Event.on :keydown do
      stop!
    end
  end
end

start ExampleGame
