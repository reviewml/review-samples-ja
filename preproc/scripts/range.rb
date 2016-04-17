#!/usr/bin/env ruby

class Hello
#@range_begin(sample)
  def hello(name)
    print "hello, #{name}!\n"
  end
#@range_end(sample)
end

if __FILE__ == $0
  Hello.new.hello("world")
end
