#include <strage/strage.hpp>

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

  }
}
