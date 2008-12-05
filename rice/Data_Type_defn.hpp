#ifndef Rice__Data_Type_defn__hpp_
#define Rice__Data_Type_defn__hpp_

#include "Class_defn.hpp"
#include "Data_Type_fwd.hpp"
#include "Static_Data_Key.hpp"
#include "detail/ruby.hpp"
#include <memory>
#include <map>
#include <set>

/*!
 *  \example map/map.cpp
 */

namespace Rice
{

namespace detail
{
  class Abstract_Caster;
}

class Module;

//! The base class for all instantiations of Data_Type.
template<typename Key_T = Static_Data_Key>
class Data_Type_Base
  : public Module_impl<Class, Data_Type_Base<Key_T> >
{
public:
  //! Default constructor.
  Data_Type_Base();

  //! Constructor.
  Data_Type_Base(VALUE v);

  //! Destructor.
  virtual ~Data_Type_Base() = 0;

  // TODO: what was this comment?
  typedef std::map<VALUE, detail::Abstract_Caster *> Casters;

protected:
  virtual detail::Abstract_Caster * caster() const = 0;

  static Casters casters_;
};

//! Define a new data class in the namespace given by module.
/*! The class will have a base class of Object.
 *
 *  \param T the C++ type of the wrapped class.
 *  \param Key_T a key used for accessing static data (see Data_Type<>).
 *  \param module the the Module in which to define the class.
 *  \return the new class.
 */
template<typename T, typename Key_T>
Rice::Data_Type<T, Key_T> define_class_under(
    Object module,
    char const * name,
    Key_T key);

//! Define a new data class in the namespace given by module.
/*! The class will have a base class of Object.  The resulting Data_Type
 *  will not be sharable with other translation units.
 *
 *  \param T the C++ type of the wrapped class.
 *  \param module the the Module in which to define the class.
 *  \return the new class.
 */
template<typename T>
Rice::Data_Type<T, Static_Data_Key> define_class_under(
    Object module,
    char const * name)
{
  return define_class_under<T>(module, name, Static_Data_Key());
}

//! Define a new data class in the namespace given by module.
/*! The class with have a base class determined by Base_T (specifically,
 *  Data_Type<Base_T>::klass).  Therefore, the type Base_T must already
 *  have been registered using define_class<> or define_class_under<>.
 *
 *  \param T the C++ type of the wrapped class.
 *  \param Key_T a key used for accessing static data (see Data_Type<>).
 *  \param module the the Module in which to define the class.
 *  \return the new class.
 */
template<typename T, typename Base_T, typename Key_T>
Rice::Data_Type<T, Key_T> define_class_under(
    Object module,
    char const * name,
    Key_T key);

//! Define a new data class in the namespace given by module.
/*! The class with have a base class determined by Base_T (specifically,
 *  Data_Type<Base_T>::klass).  Therefore, the type Base_T must already
 *  have been registered using define_class<> or define_class_under<>.
 *
 *  The resulting Data_Type will not be sharable with other translation
 *  units.
 *
 *  \param T the C++ type of the wrapped class.
 *  \param module the the Module in which to define the class.
 *  \return the new class.
 */
template<typename T, typename Base_T>
Rice::Data_Type<T, Static_Data_Key> define_class_under(
    Object module,
    char const * name)
{
  return define_class_under<T, Base_T>(module, name, Static_Data_Key());
}

//! Define a new data class in the default namespace.
/*! The class will have a base class of Object.
 *
 *  \param T the C++ type of the wrapped class.
 *  \param Key_T a key used for accessing static data (see Data_Type<>).
 *  \return the new class.
 */
template<typename T, typename Key_T>
Rice::Data_Type<T, Key_T> define_class(
    char const * name,
    Key_T key);

//! Define a new data class in the default namespace.
/*! The class will have a base class of Object.  The resulting Data_Type
 *  will not be sharable with other translation units.
 *
 *  \param T the C++ type of the wrapped class.
 *  \param Key_T a key used for accessing static data (see Data_Type<>).
 *  \return the new class.
 */
template<typename T>
Rice::Data_Type<T, Static_Data_Key> define_class(
    char const * name)
{
  return define_class<T>(name, Static_Data_Key());
}

//! Define a new data class in the default namespace.
/*! The class with have a base class determined by Base_T (specifically,
 *  Data_Type<Base_T>::klass).  Therefore, the type Base_T must already
 *  have been registered using define_class<> or define_class_under<>.
 *
 *  \param T the C++ type of the wrapped class.
 *  \param Key_T a key used for accessing static data (see Data_Type<>).
 *  \param module the the Module in which to define the class.
 *  \return the new class.
 */
template<typename T, typename Base_T, typename Key_T>
Rice::Data_Type<T, Key_T> define_class(
    char const * name,
    Key_T key);

//! Define a new data class in the default namespace.
/*! The class with have a base class determined by Base_T (specifically,
 *  Data_Type<Base_T>::klass).  Therefore, the type Base_T must already
 *  have been registered using define_class<> or define_class_under<>.
 *
 *  The resulting Data_Type will not be sharable with other translation
 *  units.
 *
 *  \param T the C++ type of the wrapped class.
 *  \param Key_T a key used for accessing static data (see Data_Type<>).
 *  \param module the the Module in which to define the class.
 *  \return the new class.
 */
template<typename T, typename Base_T>
Rice::Data_Type<T, Static_Data_Key> define_class(
    char const * name)
{
  return define_class<T, Base_T>(name, Static_Data_Key());
}

//! A mechanism for binding ruby types to C++ types.
/*! This class binds run-time types (Ruby VALUEs) to compile-time types
 *  (C++ types).  The binding can occur only once.
 *
 *  The Key_T template parameter is used to ensure that multiple
 *  translation units do not accidentally overwrite each others' static
 *  data.  It defaults to Static_Data_Key, which prevents multiple
 *  translation units from sharing data.
 *
 *  If data sharing is desired, Key_T can be explicitly specified, e.g.:
 *  \code
 *    class Foo;
 *    class My_Key;
 *    Data_Type<Foo, My_Key> rb_cFoo;
 *  \endcode
 *
 *  \param T the C++ type of the wrapped class.
 *  \param Key_T a key used for accessing static data.
 */
template<typename T, typename Key_T>
class Data_Type
  : public Module_impl<Data_Type_Base<Key_T>, Data_Type<T, Key_T> >
{
public:
  //! The C++ type being held.
  typedef T Type;

  //! Default constructor which does not bind.
  /*! No member functions must be called on this Data_Type except bind,
   *  until the type is bound.
   */
  Data_Type();

  //! Constructor which takes a Module.
  /*! Binds the type to the given VALUE according to the rules given
   *  above.
   *  \param klass the module to which to bind.
   */
  Data_Type(Module const & v);

  //! Destructor.
  virtual ~Data_Type();
 
  //! Explictly return the Ruby type.
  /*! \return the ruby class to which the type is bound.
   */
  static Module klass();

  //! Assignment operator which takes a Module
  /*! \param klass must be the class to which this data type is already
   *  bound.
   *  \return *this
   */
  virtual Data_Type & operator=(Module const & klass);

  //! Define a constructor for the class.
  /*! Creates a singleton method allocate and an instance method called
   *  initialize which together create a new instance of the class.  The
   *  allocate method allocates memory for the object reference and the
   *  initialize method constructs the object.
   *  \param constructor an object that has a static member function
   *  construct() that constructs a new instance of T and sets the object's data
   *  member to point to the new instance.  A helper class Constructor
   *  is provided that does precisely this.
   *  For example:
   *  \code
   *    define_class<Foo>("Foo")
   *      .define_constructor(Constructor<Foo>());
   *  \endcode
   */
  template<typename Constructor_T>
  Data_Type<T, Key_T> & define_constructor(
      Constructor_T constructor);

  //! Convert ruby object x to type T.
  /*! \param x the object to convert.
   *  \return the C++ object wrapped inside object x.
   */
  static T * from_ruby(Object x);

  //! Determine if the type is bound.
  /*! \return true if the object is bound, false otherwise.
   */
  static bool is_bound();

protected:
  //! Bind a Data_Type to a VALUE.
  /*! Throws an exception if the Data_Type is already bound to a
   *  different class.  Any existing instances of the Data_Type will be
   *  bound after this function returns.
   *  \param klass the ruby type to which to bind.
   *  \return *this
   */
  template<typename Base_T>
  static Data_Type bind(Module const & klass);

  template<typename T_, typename Key_T_>
  friend Rice::Data_Type<T_, Key_T_> define_class_under(
      Object module,
      char const * name,
      Key_T_ key);

  template<typename T_, typename Base_T_, typename Key_T_>
  friend Rice::Data_Type<T_, Key_T_> define_class_under(
      Object module,
      char const * name,
      Key_T_ key);

  template<typename T_, typename Key_T_>
  friend Rice::Data_Type<T_, Key_T_> Rice::define_class(
      char const * name,
      Key_T_ key);

  template<typename T_, typename Base_T_, typename Key_T_>
  friend Rice::Data_Type<T_, Key_T_> define_class(
      char const * name,
      Key_T_ key);

private:
  template<typename T_, typename Key_T_>
  friend class Data_Type;

  virtual detail::Abstract_Caster * caster() const;

  static void check_is_bound();

  static VALUE klass_;
  static std::auto_ptr<detail::Abstract_Caster> caster_;

  typedef std::set<Data_Type<T> *> Instances;

  static Instances & unbound_instances()
  {
    static Instances unbound_instances;
    return unbound_instances;
  }
};


} // namespace Rice

#include "Data_Type.ipp"

#endif // Rice__Data_Type_defn__hpp_

