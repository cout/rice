#include "Foo.hpp"

#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

using namespace Rice;

extern "C"
void Init_t1()
{
  define_class<Foo>("Foo")
    .define_constructor(Constructor<Foo>())
    .define_method("foo", &Foo::foo);
}

