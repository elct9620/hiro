# Animator Component
class Animator < Component
  attr_accessor :fps
  attr_reader :frames, :current

  def initialize(width, height, frames = 0)
    super()
    @width = width
    @height = height
    init_state
    init_ticks
    init_frame(frames)
  end

  def init_state
    # TODO: Use state machine to manage
    @playing = true
    @once = false
    @loop = 0
    @last = nil
  end

  def init_ticks
    @fps = 60
    @fixed_next_ticks = 1000 / 60
    @next_tick = 0
  end

  def init_frame(frames)
    @range = Vector2.new(0, 0)
    @frames = frames
    @frame = 0
    @keyframes = {}
    @current = nil
    @queue = []
  end

  def update(ticks)
    return unless @playing
    return if renderer.nil?
    return if @next_tick > ticks
    force_renderer_use_clip_mode
    setup_frame
    update_frame
    @next_tick += @fixed_next_ticks
  end

  def renderer
    game_object.renderer
  end

  def force_renderer_use_clip_mode
    return if renderer.clip?
    renderer.clip = true
    renderer.bound = Rectangle.new(0, 0, @width, @height)
  end

  def setup_frame
    return if frames > 0
    sprite_width, sprite_height = sprite_size.to_a
    @range.x = (sprite_width / @width).ceil
    @range.y = (sprite_height / @height).ceil
    # Set default frames
    @frames = @range.x * @range.y
  end

  def keyframes
    @keyframes[@current] || [0]
  end

  def set(name, frames)
    return unless frames.is_a?(Array)
    @keyframes[name.to_sym] = frames
    self
  end

  def to_animation(name)
    @current = name
    @frame = 0
    @loop = 0
  end

  def to(name, once = false)
    name = name.to_sym
    return unless @keyframes.key?(name)
    to_animation(name)
    @once = once
    @last = @current unless @once
    self
  end

  def to_queue(name)
    name = name.to_sym
    return unless @keyframes.key?(name)
    to_animation(name)
    @once = true
    self
  end

  def and_to(name)
    @last = @current unless @once
    @queue << name.to_sym
    self
  end

  def frame
    keyframes[@frame]
  end

  def create_bound
    x = (frame % @range.x) * @width
    y = (((frame + 1) / @range.x).ceil - 1) * @height
    Rectangle.new(x, y, @width, @height)
  end

  def update_frame
    @frame = (@frame + 1) % keyframes.size
    # TODO: @frame.zero? ( 1.2.0 not support )
    @loop += 1 unless @frame > 0
    renderer.bound = create_bound
    back_last_animation if @loop > 0 && @once
  end

  def back_last_animation
    if @queue.empty?
      to(@last) unless @last.nil?
    else
      to_queue(@queue.shift)
    end
  end

  def stop
    @playing = false
  end

  def fps=(speed)
    @fps = speed
    @fixed_next_ticks = 1000 / @fps
  end
end
