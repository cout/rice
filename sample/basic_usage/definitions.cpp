#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Module.hpp"
#include "rice/global_function.hpp"

#include <string>
#include <iostream>

using namespace Rice;

/**
 * Start with some global methods
 */
void printSomething() { std::cout << "Print this" << std::endl; }
int getNumber() { return 1; }
float getFloat() { return 4.3; }
std::string getString() { return "Hi Ruby!"; }

/**
 * Add some parameters
 */
int addNumbers(int a, int b) { return a + b; }
std::string makeString(std::string input) { return "I gots " + input; }

/**
 * Now jump into classes
 */
class Tester {
  public:
    Tester() { mInternal = "In Tester"; }

    // No parameters, no return
    void printClassName() { std::cout << "Tester" << std::endl; }

    // Basic gets
    int getNumber() { return 14; }
    std::string getString() { return mInternal; }

    // Gets with paramters
    int addNumbers(int a, int b) { return a + b; }
    
    // Modifying internal structure 
    void setInternal(std::string newInternal) { mInternal = newInternal; }

  private:
    std::string mInternal;
};

/**
 * We can use C functions to wrap into objects too!
 */
std::string getFromExternal(Tester* self) {
  return self->getString();
}

std::string setAndGet(Tester* self, std::string newStr) {
  self->setInternal(newStr);
  return self->getString();
}


extern "C"
void Init_definitions(void)
{
  RUBY_TRY
  {
    // Global methods put into Kernel
    define_global_function("print_something", &printSomething);
    define_global_function("get_number", &getNumber);
    define_global_function("get_float", &getFloat);
    define_global_function("get_string", &getString);
    define_global_function("add_numbers", &addNumbers);
    define_global_function("make_string", &makeString);

    // Class wrapper
    define_class<Tester>("Tester")
      .define_constructor(Constructor<Tester>())
      .define_method("print_class_name", &Tester::printClassName)
      .define_method("get_number", &Tester::getNumber)
      .define_method("add_numbers", &Tester::addNumbers)

      // Make methods consistent in Ruby
      .define_method("set_internal", &Tester::setInternal)
      .define_method("get_internal", &Tester::getString)

      .define_method("set_and_get", &setAndGet)
      .define_method("get_external", &getFromExternal);

      // TODO define_accessor("internal", &Tester::getString, &Tester::setInternal);

  }
  RUBY_CATCH
}

