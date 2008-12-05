#ifndef Rice__Static_Data_Key__hpp_
#define Rice__Static_Data_Key__hpp_

namespace Rice
{

namespace
{

//! The default "key" for accessing static member data.
/*! This class is used as a template parameter to class templates to
 *  prevent multiple translation units from accidentally overwriting
 *  each other's static data.
 *
 *  This class is defined in the anonymous namespace so that it is
 *  unique per translation unit.
 *
 *  Example usage:
 *  \code
 *    class Foo;
 *    Data_Type<Foo> rb_cFoo; // uses Static_Data_Key by default
 *  \endcode
 *
 *  If two translation units do want to share data, they can do so by
 *  explicitly specifying the key.
 *
 *  (The reason this is necessary is that on some platforms, loading two
 *  Rice extensions means that the symbols in the most recently loaded
 *  extension override the symbols defined in extensions loaded
 *  previously.  The result is that without this key, only the most
 *  recently loaded Rice extension can be used).
 */
class Static_Data_Key { };

} // namespace

} // namespace Rice

#endif // Rice__Static_Data_Key__hpp_
