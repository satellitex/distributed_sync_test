#include <strage/strage.hpp>
#include <strage/validator.hpp>

namespace sync {
  namespace strage {
    bool validate(const Block &block) {
      int x = block.id();

      if( strage::strage().empty() ) {
        if( x == 0 && block.hash() == 0 ) return true;
        return false;
      }

      auto &top = strage::strage().back();
      if (top.id() + 1 == x)
        if (block.hash() == top.hash() + x) return true;
      return false;
    }
  }
}
