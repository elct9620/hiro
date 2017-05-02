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
