#ifndef DISTRIBUTED_SYNC_COMMITHANDLER_HPP
#define DISTRIBUTED_SYNC_COMMITHANDLER_HPP

#include <endpoint.pb.h>

namespace commit {
  namespace handler {
    using Block = sync::protocol::Block;
    void handle(const Block&);
  }
}


#endif //DISTRIBUTED_SYNC_COMMITHANDLER_HPP
