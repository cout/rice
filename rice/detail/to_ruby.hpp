#ifndef Rice__detail__to_ruby__hpp_
#define Rice__detail__to_ruby__hpp_

#include "../Static_Data_Key.hpp"

namespace Rice
{
  namespace detail
  {
    template<typename T, typename Key_T = Static_Data_Key>
    struct to_ruby_
    {
      static Rice::Object convert(T & x);
    };

    template<typename T, typename Key_T>
    struct to_ruby_<T *, Key_T>
    {
      static Rice::Object convert(T * x);
    };
  } // detail
} // Rice

#endif // Rice__detail__to_ruby__hpp_
