#include <strage/strage.hpp>
#include <algorithm>

namespace sync {
  namespace strage {

    Strage& strage() {
      static Strage strage_;
      return strage_;
    }

    Status& status(){
      static Status status_;
      return status_;
    }

    Peers& peers(){
      static Peers peers_;
      return peers_;
    }


    void addPeer(const std::string& ip){
      if( std::find(peers().begin(),peers().end(),ip) == peers().end() )
        peers().emplace_back(ip);
    }
  }
}
