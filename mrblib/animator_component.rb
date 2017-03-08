class AnimatorComponent
  attr_accessor :animations

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

  def current
    @animations[@current] || @animations[@animations.keys.first] || [0]
  end

  def update
    is_animation = !@game_object.renderer.nil? && @game_object.renderer.animate?
    return unless is_animation
    @game_object.renderer.frame = current[@frame]
    @frame = (@frame + 1) %  current.size
    self
  end
end
