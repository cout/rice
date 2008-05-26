#ifndef Rice__Thread__hpp_
#define Rice__Thread__hpp_

#include "Object.hpp"

namespace Rice
{

class Exception;

class Thread
  : public Object
{
public:
  typedef std::unary_function<Thread, Object> Thread_Function;

  //! Wrap an existing thread
  Thread(Object thread);

  //! Wrap an existing thread
  explicit Thread(VALUE thread);

  //! Start a new thread that calls function
  Thread(Thread_Function function);

  //! Invoke the thread scheduler
  static void schedule();

  //! An alias for schedule()
  static void pass();

  //! Suspend the current thread for the specified number of seconds
  static void sleep(int seconds);

  //! Suspend the current thread indefinitely
  static void sleep();

  //! An alias for sleep()
  static void sleep_forever();

  //! Stops execution of the current thread and schedules execution of
  //! another thread
  static Object stop();

  //! Returns a reference to the current thread
  static Thread current();

  //! Returns a reference to the main thread
  static Thread main();

  //! Marks the thread as eligible for scheduling
  Thread wakeup();

  //! Wakes the thread up and makes it eligible for scheduling.
  /*! This function invokes the scheduler if not in a critical section.
   */
  Thread run();

  //! Terminates the thread and schedules another to be run
  Thread kill();

  //! Raise an exception in the thread
  Object raise(Exception const & ex);

  //! Joins the thread and returns its result
  Object join();

private:
  class Proxy;

public:
  //! Gets/sets thread-specific data for the thread
  Proxy operator[](Identifier key);

private:
  Thread_Function function_;
};

class Thread::Proxy
{
public:
	//! Construct a new Proxy
	Proxy(Thread thread, Identifier key);

	//! Implicit conversion to Object
	operator Object() const;

	//! Explicit conversion to VALUE
	VALUE value() const;

	//! Assignment operator
	Object operator=(Object value);

	//! Assignment operator
	template<typename T>
	Object operator=(T const & value);

private:
	Thread thread_;
	Identifier key_;
};

} // namespace Rice

#include "Thread.ipp"

#endif // Rice__Thread__hpp_

