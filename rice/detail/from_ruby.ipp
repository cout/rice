#ifndef Rice__detail__from_ruby__ipp_
#define Rice__detail__from_ruby__ipp_

#include "../Data_Type.hpp"
#include "../String.hpp"
#include "demangle.hpp"
#include <typeinfo>

template<typename T, typename Key_T>
T Rice::detail::from_ruby_<T, Key_T>::
convert(Rice::Object x)
{
  if(rb_type(x.value()) == T_DATA)
  {
    return *Data_Type<T, Key_T>::from_ruby(x);
  }
  else
  {
    std::string s("Unable to convert ");
    s += x.class_of().name().c_str();
    s += " to ";
    s += demangle(typeid(T).name());
    throw std::invalid_argument(s.c_str());
  }
}

template<typename T, typename Key_T>
T * Rice::detail::from_ruby_<T *, Key_T>::
convert(Rice::Object x)
{
  if(rb_type(x.value()) == T_DATA)
  {
    return Data_Type<T, Key_T>::from_ruby(x);
  }
  else
  {
    std::string s("Unable to convert ");
    s += x.class_of().name().c_str();
    s += " to ";
    s += demangle(typeid(T *).name());
    throw std::invalid_argument(s.c_str());
  }
}

template<typename T, typename Key_T>
T const * Rice::detail::from_ruby_<T const *>::
convert(Rice::Object x)
{
  return from_ruby<T *, Key_T>(x);
}

template<typename T, typename Key_T>
T & Rice::detail::from_ruby_<T &>::
convert(Rice::Object x)
{
  return *from_ruby<T *, Key_T>(x);
}

#endif // Rice__detail__from_ruby__ipp_

