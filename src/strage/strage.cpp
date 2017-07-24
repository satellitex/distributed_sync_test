//
// Created by Takumi Yamashita on 2017/07/24.
//

#include <strage/strage.hpp>

namespace sync{
  namespace strage {
    Strage& strage(){
      static Strage strage_;
      return strage_;
    }
  }
}
