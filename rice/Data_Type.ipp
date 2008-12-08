#ifndef Rice__Data_Type__ipp_
#define Rice__Data_Type__ipp_

#include "Class.hpp"
#include "String.hpp"
#include "Data_Object.hpp"
#include "detail/default_allocation_func.hpp"
#include "detail/creation_funcs.hpp"
#include "detail/method_data.hpp"
#include "detail/Caster.hpp"
#include "detail/demangle.hpp"

#include <stdexcept>
#include <typeinfo>

template<typename Key_T>
typename Rice::Data_Type_Base<Key_T>::Casters
Rice::Data_Type_Base<Key_T>::casters_;

template<typename T, typename Key_T>
VALUE Rice::Data_Type<T, Key_T>::klass_ = Qnil;

template<typename T, typename Key_T>
std::auto_ptr<Rice::detail::Abstract_Caster> Rice::Data_Type<T, Key_T>::caster_;

template<typename Key_T>
Rice::Data_Type_Base<Key_T>::
Data_Type_Base()
  : Module_impl<Class, Data_Type_Base<Key_T> >()
{
}

template<typename Key_T>
Rice::Data_Type_Base<Key_T>::
Data_Type_Base(VALUE v)
  : Module_impl<Class, Data_Type_Base<Key_T> >(v)
{
}

template<typename Key_T>
Rice::Data_Type_Base<Key_T>::
~Data_Type_Base()
{
}

template<typename T, typename Key_T>
template<typename Base_T>
inline Rice::Data_Type<T, Key_T> Rice::Data_Type<T, Key_T>::
bind(Module const & klass)
{
  if(klass.value() == klass_)
  {
    return Data_Type<T, Key_T>();
  }

  if(is_bound())
  {
    std::string s;
    s = "Data type ";
    s = typeid(T).name();
    s += " is already bound to a different type";
    throw std::runtime_error(s.c_str());
  }

  // TODO: Make sure base type is bound; throw an exception otherwise.
  // We can't do this just yet, because we don't have a specialization
  // for binding to void.
  klass_ = klass;

  // TODO: do we need to unregister when the program exits?  we have to
  // be careful if we do, because the ruby interpreter might have
  // already shut down.  The correct behavior is probably to register an
  // exit proc with the interpreter, so the proc gets called before the
  // GC shuts down.
  rb_gc_register_address(&klass_);

  for(typename Instances::iterator it = unbound_instances().begin(),
      end = unbound_instances().end();
      it != end;
      unbound_instances().erase(it++))
  {
    (*it)->set_value(klass);
  }

  detail::Abstract_Caster * base_caster = Data_Type<Base_T>().caster();
  caster_.reset(new detail::Caster<T, Base_T>(base_caster, klass));
  Data_Type_Base<Key_T>::casters_.insert(std::make_pair(klass, caster_.get()));
  return Data_Type<T, Key_T>();
}

template<typename T, typename Key_T>
inline Rice::Data_Type<T, Key_T>::
Data_Type()
  : Module_impl<Data_Type_Base<Key_T>, Data_Type<T> >(
      klass_ == Qnil ? rb_cObject : klass_)
{
  if(!is_bound())
  {
    unbound_instances().insert(this);
  }
}

template<typename T, typename Key_T>
inline Rice::Data_Type<T, Key_T>::
Data_Type(Module const & klass)
  : Module_impl<Data_Type_Base<Key_T>, Data_Type<T, Key_T> >(
      klass)
{
  this->bind<void>(klass);
}

template<typename T, typename Key_T>
inline Rice::Data_Type<T, Key_T>::
~Data_Type()
{
  unbound_instances().erase(this);
}

template<typename T, typename Key_T>
Rice::Module
Rice::Data_Type<T, Key_T>::
klass() {
  if(is_bound())
  {
    return klass_;
  }
  else
  {
    std::string s;
    s += detail::demangle(typeid(T *).name());
    s += " is unbound";
    throw std::runtime_error(s.c_str());
  }
}

template<typename T, typename Key_T>
Rice::Data_Type<T, Key_T> & Rice::Data_Type<T, Key_T>::
operator=(Module const & klass)
{
  this->bind<void>(klass);
  return *this;
}

template<typename T, typename Key_T>
template<typename Constructor_T>
inline Rice::Data_Type<T, Key_T> & Rice::Data_Type<T, Key_T>::
define_constructor(
    Constructor_T constructor)
{
  check_is_bound();

  // Normal constructor pattern with new/initialize
  detail::define_alloc_func(
      static_cast<VALUE>(*this),
      detail::default_allocation_func<T>);
  define_method("initialize", &Constructor_T::construct);

  return *this;
}

template<typename T, typename Key_T>
inline T * Rice::Data_Type<T, Key_T>::
from_ruby(Object x)
{
  check_is_bound();

  void * v = DATA_PTR(x.value());
  Class klass = x.class_of();

  if(klass.value() == klass_)
  {
    // Great, not converting to a base/derived type
    Data_Type<T> data_klass;
    Data_Object<T> obj(x, data_klass);
    return obj.get();
  }

  typename Data_Type_Base<Key_T>::Casters::const_iterator it(
      Data_Type_Base<Key_T>::casters_.find(klass));
  if(it == Data_Type_Base<Key_T>::casters_.end())
  {
    std::string s = "Derived class ";
    s += klass.name().str();
    s += " is not registered/bound in Rice";
    throw std::runtime_error(s);
  }

  detail::Abstract_Caster * caster = it->second;
  if(caster)
  {
    T * result = static_cast<T *>(caster->cast_to_base(v, klass_));
    return result;
  }
  else
  {
    return static_cast<T *>(v);
  }
}

template<typename T, typename Key_T>
inline bool Rice::Data_Type<T, Key_T>::
is_bound()
{
  return klass_ != Qnil;
}

template<typename T, typename Key_T>
inline Rice::detail::Abstract_Caster *
Rice::Data_Type<T, Key_T>::
caster() const
{
  check_is_bound();
  return caster_.get();
}

namespace Rice
{

template<>
inline detail::Abstract_Caster * Data_Type<void>::
caster() const
{
  return 0;
}

template<typename T, typename Key_T>
void Data_Type<T, Key_T>::
check_is_bound()
{
  if(!is_bound())
  {
    std::string s;
    s = "Data type ";
    s = typeid(T).name();
    s += " is not bound";
    throw std::runtime_error(s.c_str());
  }
}

} // Rice

template<typename T, typename Key_T>
inline Rice::Data_Type<T, Key_T> Rice::
define_class_under(
    Object module,
    char const * name,
    Key_T /* key */)
{
  Class c(define_class_under(module, name, rb_cObject));
  c.undef_creation_funcs();
  return Data_Type<T, Key_T>::template bind<void>(c);
}

template<typename T, typename Base_T, typename Key_T>
inline Rice::Data_Type<T, Key_T> Rice::
define_class_under(
    Object module,
    char const * name,
    Key_T /* key */)
{
  Data_Type<Base_T> base_dt;
  Class c(define_class_under(module, name, base_dt));
  c.undef_creation_funcs();
  return Data_Type<T, Key_T>::template bind<Base_T>(c);
}

template<typename T, typename Key_T>
inline Rice::Data_Type<T, Key_T> Rice::
define_class(
    char const * name,
    Key_T /* key */)
{
  Class c(define_class(name, rb_cObject));
  c.undef_creation_funcs();
  return Data_Type<T, Key_T>::template bind<void>(c);
}

template<typename T, typename Base_T, typename Key_T>
inline Rice::Data_Type<T, Key_T> Rice::
define_class(
    char const * name,
    Key_T /* key */)
{
  Data_Type<Base_T> base_dt;
  Class c(define_class(name, base_dt));
  c.undef_creation_funcs();
  return Data_Type<T, Key_T>::template bind<Base_T>(c);
}

#endif // Rice__Data_Type__ipp_
