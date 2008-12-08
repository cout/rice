#ifndef Rice__detail__from_ruby__hpp_
#define Rice__detail__from_ruby__hpp_

namespace Rice
{
  namespace detail
  {
    template<typename T, typename Key_T>
    struct from_ruby_
    {
      typedef T Retval_T;

      static T convert(Rice::Object x);
    };

    template<typename T, typename Key_T>
    struct from_ruby_<T *, Key_T>
    {
      typedef T * Retval_T;

      static T * convert(Rice::Object x);
    };

    template<typename T, typename Key_T>
    struct from_ruby_<T const *, Key_T>
    {
      typedef T const * Retval_T;

      static T const * convert(Rice::Object x);
    };

    template<typename T, typename Key_T>
    struct from_ruby_<T &, Key_T>
    {
      typedef T & Retval_T;

      static T & convert(Rice::Object x);
    };
  } // detail
} // Rice

#endif // Rice__detail__from_ruby__hpp_

