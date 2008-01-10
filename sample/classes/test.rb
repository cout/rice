require 'classes'

c = Tester.new
puts "The name of the class from C++ is: "
c.print_class_name

puts ""
puts "1 + 2 == #{c.add_numbers(1, 2)}"
puts "Internal string is \"#{c.get_internal}\""
puts "Setting internal string to \"This is cool!\""
c.set_internal("This is cool!")
puts "Internal string is now: \"#{c.get_internal}\""

puts ""
puts "C functions are also wrapped into the class: #{c.get_external}"
puts "Setting to \"Wootage\" and getting it back: #{c.set_and_get("Wootage")}"
