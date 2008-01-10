#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Module.hpp"
#include "rice/global_function.hpp"

#include <string>
#include <iostream>

using namespace Rice;

/**
 * Rice allows for very easy wrapping of C++ classes and 
 * structs
 */
class Tester {
  public:
    Tester() { mInternal = "In Tester"; }
    Tester(std::string set) { mInternal = set; }

    void printClassName() { std::cout << "Tester" << std::endl; }

    int addNumbers(int a, int b) { return a + b; }
    
    void setInternal(std::string newInternal) { mInternal = newInternal; }
    std::string getInternal() { return mInternal; }

  private:
    std::string mInternal;
};

/**
 * We can use C functions to wrap into objects too!
 */
std::string getFromExternal(Tester* self) {
  return self->getInternal();
}

std::string setAndGet(Tester* self, std::string newStr) {
  self->setInternal(newStr);
  return self->getInternal();
}


extern "C"
void Init_classes(void)
{
  RUBY_TRY
  {
    // Class wrapper
    define_class<Tester>("Tester")
      //.define_constructor(Constructor<Tester>())
      .define_constructor(Constructor<Tester, std::string>())
      .define_method("print_class_name", &Tester::printClassName)
      .define_method("add_numbers", &Tester::addNumbers)

      // Make methods consistent in Ruby
      .define_method("set_internal", &Tester::setInternal)
      .define_method("get_internal", &Tester::getInternal)

      .define_method("set_and_get", &setAndGet)
      .define_method("get_external", &getFromExternal);
  }
  RUBY_CATCH
}

