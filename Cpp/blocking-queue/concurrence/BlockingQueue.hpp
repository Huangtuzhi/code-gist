#include <queue>
#include <iostream>
#include "Condition.hpp"
#include <ctime>
using namespace std;

namespace GistUtil {
template<class T>
class BlockingQueue: NonCopyable {
 public:
  BlockingQueue(int queueSize)
    : mutex_(), notEmpty_(mutex_), notFullCondition_(mutex_), queue_(), maxElementSize_(queueSize) {
  }

  BlockingQueue()
    : mutex_(), notEmpty_(mutex_), notFullCondition_(mutex_), queue_(), maxElementSize_(500) {
  }

  void Push(const T& x) {
    MutexLockGuard lock(mutex_);
    queue_.push(x);
    notEmpty_.Notify(); // Wait morphing saves us
  }

  T Pop() {
    MutexLockGuard lock(mutex_);
    // always use a while-loop, due to spurious wakeup
    while (queue_.empty()) {
      notEmpty_.Wait();
    }
    assert(!queue_.empty());
    T front(queue_.front());
    queue_.pop();
    return front;
  }

  bool TimedPush(const T& x, int timeOutMs) {
    bool success = false;
    {
      MutexLockGuard lock(mutex_);
      // 队列满则阻塞等待 timeOutMs 时间
      if (UnlockedIsFull()) {
        cout << "\n queue is full, queue_size=" << queue_.size() 
             << "|time=" << time(NULL) << endl;
        notFullCondition_.Wait(timeOutMs);
      }

      // 等待之后再次判断条件是否成立
      if (!UnlockedIsFull()) {
        queue_.push(x);
        success = true;
        // cout << "\n TimedPush succ " << endl;
      }
    }

    // 入队成功，通知 notEmpty_ 条件成立
    if (success) {
      notEmpty_.Notify();
    }
    return success;
  }

  bool TimedPop(T* value, int timeOutMs) {
    bool success = false;
    {
      MutexLockGuard lock(mutex_);

      if (queue_.empty()) {
        // 阻塞等待 timeOutMs 时间
        cout << "\n queue is empty, queue_size=" << queue_.size() 
             << "|time=" << time(NULL) << endl;
        notEmpty_.Wait(timeOutMs);
      }

      // 等待之后再次判断条件是否成立
      if (!queue_.empty()) {
        *value = queue_.front();
        queue_.pop();
        success = true;
      }
    } // 锁释放

    // 出队成功，通知 notFullCondition_ 条件成立
    if (success) {
      notFullCondition_.Notify();
    }
    return success;
  }

  size_t Size() const {
    MutexLockGuard lock(mutex_);
    return queue_.size();
  }
  bool Empty() const {
    return Size() == 0;
  }

  bool IsFull() const {
    MutexLockGuard lock(mutex_);
    return UnlockedIsFull();
  }

private:
  bool UnlockedIsFull() const {
    return queue_.size() >= maxElementSize_;
  }

 private:
  mutable MutexLock mutex_;
  Condition         notEmpty_;
  Condition         notFullCondition_;
  std::queue<T>     queue_;
  int maxElementSize_;
}; // class BlockingQueue

}
