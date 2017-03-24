class RendererComponent
  attr_accessor :width, :height, :frame
  attr_reader :frames, :scale

  def animate?
    @animate
  end
end
