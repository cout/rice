#include "Thread.hpp"
#include "Exception.hpp"

Rice::Thread::
Thread(Object thread)
  : Object(thread)
{
}

Rice::Thread::
Thread(VALUE thread)
  : Object(thread)
{
}


Rice::Thread::
Thread(Thread_Function function)
  : function_(function)
{
  // TODO: start thread
}

namespace
{
  VALUE thread_schedule()
  {
    rb_thread_schedule();
    return Qnil;
  }
}

void Rice::Thread::
schedule()
{
  protect(thread_schedule);
}

void Rice::Thread::
pass()
{
  schedule();
}

namespace
{
  VALUE thread_sleep(int seconds)
  {
    rb_thread_sleep(seconds);
    return Qnil;
  }
}

void Rice::Thread::
sleep(int seconds)
{
  protect(thread_sleep, seconds);
}

namespace
{
  VALUE thread_sleep_forever()
  {
    rb_thread_sleep_forever();
    return Qnil;
  }
}

void Rice::Thread::
sleep()
{
  protect(thread_sleep_forever);
}

void Rice::Thread::
sleep_forever()
{
  return sleep();
}

Rice::Object Rice::Thread::
stop()
{
  return protect(rb_thread_stop);
}

Rice::Thread Rice::Thread::
current()
{
  return Thread(protect(rb_thread_current));
}

Rice::Thread Rice::Thread::
main()
{
  return Thread(protect(rb_thread_main));
}

Rice::Thread Rice::Thread::
wakeup()
{
  return Thread(protect(rb_thread_wakeup, *this));
}

Rice::Thread Rice::Thread::
run()
{
  return Thread(protect(rb_thread_run, *this));
}

Rice::Thread Rice::Thread::
kill()
{
  return Thread(protect(rb_thread_kill, *this));
}

Rice::Object Rice::Thread::
raise(Exception const & ex)
{
  return call("raise", ex);
}

Rice::Object Rice::Thread::
join()
{
  return call("join");
}

Rice::Thread::Proxy Rice::Thread::
operator[](Identifier key)
{
  return Proxy(*this, key);
}

Rice::Thread::Proxy::
Proxy(Thread thread, Identifier key)
  : thread_(thread)
  , key_(key)
{
}

Rice::Thread::Proxy::
operator Object() const
{
  return protect(rb_thread_local_aref, thread_, key_);
}

VALUE Rice::Thread::Proxy::
value() const
{
  return Object(*this).value();
}

Rice::Object Rice::Thread::Proxy::
operator=(Object value)
{
	protect(rb_thread_local_aset, thread_, key_, value);
  return value;
}

