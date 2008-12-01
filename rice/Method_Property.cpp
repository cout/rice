#include "Method_Property.hpp"
#include "detail/ruby.hpp"

// TODO: This is silly, autoconf...
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#include "config.hpp"

#if defined(HAVE_NODE_H)
/* pre-YARV */
#include <node.h>
#elif defined(REALLY_HAVE_RUBY_NODE_H)
/* YARV */
#include <ruby/node.h>
#else
/* YARV without node.h */
#include "mininode.hpp"
using namespace Rice::detail::Mininode;
#endif

#include <stdexcept>

Rice::Method_Property::
Method_Property()
  : visibility_(V_PUBLIC)
  , visibility_is_set_(false)
{
}

Rice::Method_Property
Rice::Method_Property::
combine_with(
    Method_Property const & rhs)
{
  Method_Property new_property(*this);

  if(rhs.visibility_is_set_)
  {
    new_property.visibility_ = rhs.visibility_;
  }

  return new_property;
}

Rice::Method_Property
Rice::Method_Property::
operator|(
    Method_Property const & rhs)
{
  return this->combine_with(rhs);
}

Rice::Method_Property::Visibility
Rice::Method_Property::
visibility() const
{
  return visibility_;
}

Rice::Method_Property &
Rice::Method_Property::
public_visibility()
{
  visibility_ = V_PUBLIC;
  return *this;
}

Rice::Method_Property &
Rice::Method_Property::
private_visibility()
{
  visibility_ = V_PRIVATE;
  return *this;
}

Rice::Method_Property &
Rice::Method_Property::
protected_visibility()
{
  visibility_ = V_PROTECTED;
  return *this;
}

int Rice::Method_Property::
noex() const
{
  switch(visibility_)
  {
    case V_PUBLIC:
      return NOEX_PUBLIC;

    case V_PRIVATE:
      return NOEX_PRIVATE;

    case V_PROTECTED:
      return NOEX_PROTECTED;
  }

  throw std::logic_error("Invalid visibility");
}

Rice::Method_Property
Rice::
public_visibility()
{
  return Method_Property().public_visibility();
}

Rice::Method_Property
Rice::
private_visibility()
{
  return Method_Property().private_visibility();
}

Rice::Method_Property
Rice::
protected_visibility()
{
  return Method_Property().protected_visibility();
}

