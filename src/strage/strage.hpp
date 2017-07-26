#ifndef DISTRIBUTED_SYNC_STRAGE_HPP
#define DISTRIBUTED_SYNC_STRAGE_HPP

#include <endpoint.pb.h>

#include <exception>
#include <string>
#include <vector>

namespace sync {
  namespace strage {
    using Block = sync::protocol::Block;
    using Strage = std::vector<Block>;
    using Peers = std::vector<std::string>;

    class Status {
     public:
      Status() { status_ = false; }
      void activate() { status_ = true; }
      void stop() { status_ = false; }
      bool synced() const { return status_ == true; }
      bool unsynced() const { return status_ != true; }

     private:
      bool status_;
    };

    Peers& peers();
    Strage& strage();
    Status& status();
  }
}
#endif  // DISTRIBUTED_SYNC_STRAGE_HPP
