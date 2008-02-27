#include "Proc.hpp"

Rice::Proc::
Proc(Object o)
  : Object(o)
{
}

int Rice::Proc::
arity() const
{
  return from_ruby<int>(call("arity"));
}

Rice::Object Rice::Proc::
binding()
{
  return call("binding");
}

VALUE Rice::Proc::
call_cpp_func(VALUE yieldarg_v, VALUE procarg)
{
  RUBY_TRY
  {
    Rice::Object yieldarg(yieldarg_v);

    detail::Wrapped_Function * f(
        (detail::Wrapped_Function *)procarg);

    f->call_as_proc(yieldarg);
  }
  RUBY_CATCH

  // TODO: User-defined exception conversions?
}

