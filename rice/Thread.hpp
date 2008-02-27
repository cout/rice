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
  static void schedule();
  static void sleep();
  static void sleep_forever();
  static void stop();
  static void interrupt();
  static Thread current();

  void wakeup();
  void run();
  void kill();
  void raise(Exception const & ex);
  Object join();

  template<typename Key_T>
  Object operator[](Key_T const & key);

  template<typename Key_T, typename Value_T>
  Object operator[]=(Key_T const & key, Value_T const & value);

  virtual void start();
};

} // namespace Rice

#include "Thread.ipp"

#endif // Rice__Thread__hpp_

