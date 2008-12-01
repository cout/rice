#ifndef Rice__Method_Property__hpp
#define Rice__Method_Property__hpp

namespace Rice
{

class Method_Property
{
public:
  Method_Property();

  Method_Property combine_with(Method_Property const & rhs) const;

  Method_Property operator|(Method_Property const & rhs) const;

  enum Visibility
  {
    V_PUBLIC,
    V_PRIVATE,
    V_PROTECTED,
  };

  //! Return the visibility
  Visibility visibility() const;

  //! Set the visibility to public.
  Method_Property & public_visibility();

  //! Set the visibility to private.
  Method_Property & private_visibility();

  //! Set the visibility to protected.
  Method_Property & protected_visibility();

  int noex() const;

private:
  Visibility visibility_;
  int visibility_is_set_;
};

//! Construct a Method_Property with public visibility
Method_Property public_visibility();

//! Construct a Method_Property with private visibility
Method_Property private_visibility();

//! Construct a Method_Property with protected visibility
Method_Property protected_visibility();

} // namespace Rice

#endif // Rice__Method_Property__hpp

