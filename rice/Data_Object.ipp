#ifndef Rice__Data_Object__ipp_
#define Rice__Data_Object__ipp_

#include "detail/check_ruby_type.hpp"
#include "protect.hpp"

#include <algorithm>

template<typename T>
const typename Rice::Default_Mark_Function<T>::Ruby_Data_Func
Rice::Default_Mark_Function<T>::mark = ruby_mark<T>;

namespace Rice
{

namespace detail
{

inline VALUE data_wrap_struct(
    VALUE klass,
    RUBY_DATA_FUNC mark,
    RUBY_DATA_FUNC free,
    void * obj)
{
  return Data_Wrap_Struct(klass, mark, free, obj);
}

template<typename Key_T, typename T>
inline VALUE wrap(
    VALUE klass,
    typename Data_Object<T, Key_T>::Ruby_Data_Func mark,
    typename Data_Object<T, Key_T>::Ruby_Data_Func free,
    T * obj)
{
  // We cast to obj void* here before passing to Data_Wrap_Struct,
  // becuase otherwise compilation will fail if obj is const.  It's safe
  // to do this, because unwrap() will always add the const back when
  // the object is unwrapped.
  return Rice::protect(data_wrap_struct,
      klass,
      reinterpret_cast<RUBY_DATA_FUNC>(mark),
      reinterpret_cast<RUBY_DATA_FUNC>(free),
      (void *)obj);
}

template<typename T>
inline VALUE data_get_struct(VALUE value, T * * obj)
{
  Data_Get_Struct(value, T, *obj);
  return Qnil;
}

template<typename T>
inline T * unwrap(VALUE value)
{
  T * obj;
  Rice::protect(data_get_struct<T>, value, &obj);
  return obj;
}

} // namespace detail

} // namespace Rice

template<typename T, typename Key_T>
inline Rice::Data_Object<T, Key_T>::
Data_Object(
    T * obj,
    VALUE klass,
    Ruby_Data_Func mark_func,
    Ruby_Data_Func free_func)
  : Object(detail::wrap<Key_T>(klass, mark_func, free_func, obj))
  , obj_(obj)
{
}

template<typename T, typename Key_T>
inline Rice::Data_Object<T, Key_T>::
Data_Object(
    Object value)
  : Object(value)
  , obj_(detail::unwrap<T>(value))
{  
  Data_Type<T, Key_T> klass;
  check_cpp_type(klass);
  detail::check_ruby_type(value, klass, true);
}

template<typename T, typename Key_T>
template<typename T_, typename Key_T_>
inline Rice::Data_Object<T, Key_T>::
Data_Object(
    Object value,
    Data_Type<T_, Key_T_> const & klass)
  : Object(value)
  , obj_(detail::unwrap<T>(value))
{  
  check_cpp_type(klass);
  detail::check_ruby_type(value, klass, true);
}

template<typename T, typename Key_T>
inline Rice::Data_Object<T, Key_T>::
Data_Object(Data_Object const & other)
  : Object(other.value())
  , obj_(other.obj_)
{
}

template<typename T, typename Key_T>
template<typename T_, typename Key_T_>
inline void Rice::Data_Object<T, Key_T>::
swap(Data_Object<T_, Key_T_> & ref)
{
  std::swap(obj_, ref.obj_);
  Object::swap(ref);
}

template<typename T, typename Key_T>
inline void Rice::Data_Object<T, Key_T>::
check_cpp_type(Data_Type<T, Key_T> const & /* klass */)
{
}

template<typename T, typename Key_T>
Rice::Object Rice::detail::to_ruby_<Rice::Data_Object<T, Key_T> >::
convert(Rice::Data_Object<T, Key_T> const & x)
{
  return x;
}

#endif // Rice__Data_Object__ipp_

