#include <helper/thread_pool.hpp>

namespace helper {
  namespace thread {

    ThreadPool::ThreadPool() {}
    ThreadPool::~ThreadPool() {
      for (auto &&t : pool_) t.detach();
    }

    void ThreadPool::process(std::thread&& th) {
      pool_.emplace_back(std::move(th));
    }

    ThreadPool& pool() {
      static ThreadPool pool_;
      return pool_;
    }
  }
}
