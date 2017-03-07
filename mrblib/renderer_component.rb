class RendererComponent
  attr_accessor :width, :height, :frame
  attr_reader :frames

  def animate?
    @animate
  end
end
