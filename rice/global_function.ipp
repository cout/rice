#include "detail/define_method_and_auto_wrap.hpp"
#include "Method_Property.hpp"

template<typename Func_T>
void Rice::define_global_function(
    char const * name,
    Func_T func,
    Object handler)
{
  Module(rb_mKernel).define_module_function(
      name,
      func,
      public_visibility(),
      handler);
}

