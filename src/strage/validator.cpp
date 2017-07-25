#include <strage/strage.hpp>
#include <strage/validator.hpp>

namespace sync {
  namespace strage {
    bool validate(const Block &block) {
      int x = block.id();
      auto &top = strage::strage().back();
      if (top.id() + 1 == x)
        if (block.hash() == top.hash() + x) return true;
      return false;
    }
  }
}
