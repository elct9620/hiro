class AnimatorComponent
  attr_reader :current
  attr_accessor :animations, :fps

  def set(name, frames)
    return unless frames.is_a?(Array)
    @current = name if @animations.empty?
    @animations[name.to_sym] = frames
    self
  end

  def to(name)
    name = name.to_sym
    return unless @animations.has_key?(name)
    @current = name
    @frame = 0
    self
  end

  def fps=(fps)
    @fixed_next_ticks = 1000 / fps
    @fps = fps
  end

  def keyframes
    @animations[@current] || @animations[@animations.keys.first] || [0]
  end

  def animate_enabled?
    return false unless @game_object.respond_to?(:renderer)
    return false unless @game_object.renderer.respond_to?(:animate?)
    @game_object.renderer.animate?
  end

  def play
    @playing = true
    self
  end

  def stop
    @playing = false
    self
  end

  def playing?
    animate_enabled? && @playing
  end

  def request_next_frame(ticks)
    @frame = (@frame + 1) %  keyframes.size
    @next_ticks = @fixed_next_ticks + ticks
  end

  def update_frame
    @game_object.renderer.frame = keyframes[@frame]
  end

  def update(ticks)
    return unless playing?
    return unless ticks > @next_ticks
    update_frame
    request_next_frame ticks
    self
  end
end
