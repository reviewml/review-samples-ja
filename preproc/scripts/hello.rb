#!/usr/bin/env ruby

class Hello
  def hello(name)
    print "hello, #{name}!\n"
  end
end

if __FILE__ == $0
  Hello.new.hello("world")
end
