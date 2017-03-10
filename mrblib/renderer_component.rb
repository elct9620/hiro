class RendererComponent
  attr_accessor :width, :height, :frame, :flip
  attr_reader :frames

  def animate?
    @animate
  end
end
