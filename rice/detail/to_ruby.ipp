#include "../Data_Object.hpp"

template<typename T, typename Key_T>
Rice::Object
Rice::detail::to_ruby_<T, Key_T>::
convert(T & x)
{
  if(Data_Type<T, Key_T>::is_bound())
  {
    Data_Object<T, Key_T> obj(&x);
    return obj;
  }
  else
  {
    std::string s("Unable to convert ");
    s += demangle(typeid(T *).name());
    throw std::invalid_argument(s.c_str());
  }
}   

template<typename T, typename Key_T>
Rice::Object
Rice::detail::to_ruby_<T *, Key_T>::
convert(T * x)
{
  if(Data_Type<T, Key_T>::is_bound())
  {
    Data_Object<T, Key_T> obj(x);
    return obj;
  }
  else
  {
    std::string s("Unable to convert ");
    s += demangle(typeid(T *).name());
    throw std::invalid_argument(s.c_str());
  }
}
