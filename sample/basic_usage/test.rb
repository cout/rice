require 'definitions'

# Global methods

puts "The following should be \"Print this\""
print_something

puts "#{get_number} should be 1"
puts "#{get_float} should be around 4.3"
puts "#{get_string} should be \"Hi Ruby\""

# Methods with arguments
puts "#{add_numbers(4, 6)} should be 10"
puts "#{make_string("Rice Rocks")} should be \"I gots Rice Rocks\""

# Class
c = Tester.new
puts "The following should be \"Tester\""
c.print_class_name

puts "#{c.get_number} should be 14"
puts "#{c.add_numbers(1, 2)} should be 3"
puts "#{c.get_internal} should be \"In Tester\""
puts "Setting internal string to \"This is cool!\""
c.set_internal("This is cool!")
puts "Make sure it was set: #{c.get_internal}"

puts "#{c.get_external} should be \"This is cool!\""

puts "Setting to \"Wootage\" and getting it back: #{c.set_and_get("Wootage")}"
