#include "detail/wrapped_function.hpp"

template<typename Func_T>
Proc::
Proc(Func_T func)
{
  // TODO: memory leak (since wrap_function creates a new object)
  // We can fix this by using a Data_Object
  detail::Wrapped_Function * f(wrap_function(function, handler));
  return protect(rb_proc_new, RUBY_METHOD_FUNC(f->func()), f);
}

