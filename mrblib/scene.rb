# Scene
class Scene
  def initialize
    @objects = []
  end

  def add(object)
    return unless object.is_a?(GameObject)
    @objects.push(object)
  end

  def update; end

  def draw; end
end
