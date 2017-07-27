
#ifndef DISTRIBUTED_SYNC_THREAD_POOL_HPP
#define DISTRIBUTED_SYNC_THREAD_POOL_HPP

#include <cstring>
#include <vector>
#include <string>
#include <thread>
#include <unordered_map>

namespace helper {
  namespace thread {

    class ThreadPool {
    public:
      ThreadPool();
      ~ThreadPool();

      void process(std::thread&& th);

     private:
      std::vector<std::thread> pool_;
    };

    ThreadPool& pool();
  }
}

#endif  // DISTRIBUTED_SYNC_THREAD_POOL_HPP
