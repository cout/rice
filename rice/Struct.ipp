#include "Symbol.hpp"

inline Rice::Struct& Rice::Struct::
initialize(
    Module module,
    Identifier name)
{
  Class struct_class(rb_cStruct);

  Object type = struct_class.vcall("new", this->members());

  set_value(type);
  module.const_set(name, type);

  return *this;
}

inline Rice::Struct& Rice::Struct::
define_member(
    Identifier name)
{
  if (value() != rb_cObject)
  {
    throw std::runtime_error("struct is already initialized");
  }

  members_.push_back(name.to_sym());

  return *this;
}

inline Rice::Array Rice::Struct::
members() const
{
  if (value() == rb_cObject)
  {
    // Struct is not yet defined
    return Array(members_.begin(), members_.end());
  }
  else
  {
    // Struct is defined, call Ruby API
    return rb_struct_s_members(this->value());
  }
}

inline Rice::Struct::Instance
Rice::Struct::
  new_instance(Array args) const
{
  Object instance = const_cast<Struct*>(this)->vcall("new", args);
  return Instance(*this, instance);
}

inline Rice::Struct::Instance::
Instance(
    Struct const& type,
    Array args)
  : Builtin_Object<T_STRUCT>(type.new_instance(args))
  , type_(type)
{
}

inline Rice::Struct::Instance::
Instance(
    Struct const& type,
    Object s)
  : Builtin_Object<T_STRUCT>(s)
  , type_(type)
{
}

inline Rice::Struct Rice::
define_struct()
{
  return Struct();
}

template<typename T>
inline Rice::Object Rice::Struct::Instance::
operator[](T index)
{
  return rb_struct_aref(value(), ULONG2NUM(index));
}

template<>
inline Rice::Object Rice::Struct::Instance::
operator[]<Rice::Identifier>(Rice::Identifier member)
{
  return rb_struct_aref(value(), Symbol(member));
}

template<>
inline Rice::Object Rice::Struct::Instance::
operator[]<char const *>(char const * name)
{
  return (*this)[Identifier(name)];
}
