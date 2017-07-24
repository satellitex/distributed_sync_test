#include <string>
#include <vector>

#include <server/syncServer.hpp>
#include <strage/strage.hpp>

int main() {
  for (int i = 0; i < 1000; i++) {
    sync::protocol::Block block;
    block.set_id(std::to_string(i));
    block.set_context("context!!" + std::to_string(i));
    sync::strage::strage().emplace_back(block);
    std::cout << "emplace_back! " << i << std::endl;
  }

  sync::server::run();
}