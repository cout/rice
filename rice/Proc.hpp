#ifndef Rice__Proc__hpp_
#define Rice__Proc__hpp_

#include "Object.hpp"

namespace Rice
{

class Proc
  : public Object
{
public:
  Proc(Object o);

  template<typename Func_T>
  Proc(Func_T func);

  int arity() const;
  Object binding();

private:
  static VALUE call_cpp_func(VALUE yieldarg, VALUE procarg);
};

} // namespace Rice

#include "Proc.ipp"

#endif // Rice__Proc__hpp_
