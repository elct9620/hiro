# Event
class Event < Hash
  class << self
    def types
      {
        quit: 0x100,
        keydown: 0x300,
        keyup: 0x301
      }
    end

    def events
      @events ||= {}
    end

    def event(name)
      events[name.to_sym] ||= []
      events[name.to_sym]
    end

    def on(name, &block)
      name = name.to_sym
      return unless block_given?
      return unless types.keys.include?(name)

      event(name).push(block)
    end

    def emit(type, data)
      name = types.key(type)
      return if name.nil?
      event(name.to_sym).each { |fn| fn.call(data) }
    end
  end
end
