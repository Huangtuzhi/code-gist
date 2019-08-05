#include "MutexLock.hpp"
#include <sys/time.h>
#include <time.h>

namespace GistUtil {

void RelativeTimeInMillSecondsToAbsTimeInTimeSpec(int64_t relative_time_in_ms, 
          timespec* ts)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t usec = tv.tv_usec + relative_time_in_ms * 1000LL;
  ts->tv_sec = tv.tv_sec + usec / 1000000;
  ts->tv_nsec = (usec % 1000000) * 1000;
}

class Condition : NonCopyable {
 public:
  explicit Condition(MutexLock& mutex)
    : mutex_(mutex) {
    pthread_condattr_t cond_attr;
    XCHECK(!pthread_condattr_init(&cond_attr));
    // NULL 与默认值等价
    XCHECK(!pthread_cond_init(&pcond_, &cond_attr));
    XCHECK(!pthread_condattr_destroy(&cond_attr));
  }

  ~Condition() {
    XCHECK(!pthread_cond_destroy(&pcond_));
  }

  void Wait() {
    XCHECK(!pthread_cond_wait(&pcond_, mutex_.GetPthreadMutex()));
  }

  bool Wait( int timeout_in_ms) {
    if (timeout_in_ms < 0) {
      Wait();
      return true;
    }

    timespec ts;
    RelativeTimeInMillSecondsToAbsTimeInTimeSpec(timeout_in_ms, &ts);
    // 这里死锁不返回
    return !pthread_cond_timedwait(&pcond_, mutex_.GetPthreadMutex(), &ts);
  }

  void Notify() {
    XCHECK(!pthread_cond_signal(&pcond_));
  }

  void NotifyAll() {
    XCHECK(!pthread_cond_broadcast(&pcond_));
  }

 private:
  MutexLock& mutex_;
  pthread_cond_t pcond_;
}; // class Condition

}
