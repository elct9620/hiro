module Event
  class Data < Hash
    private

    def method_missing(name, *args, &block)
      return self[name] unless self[name].nil?
      super
    end
  end
end
