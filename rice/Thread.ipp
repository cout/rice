#include "to_from_ruby.hpp"

template<typename T>
Rice::Object Rice::Thread::Proxy::
operator=(T const & value)
{
	*this = to_ruby(value);
}

