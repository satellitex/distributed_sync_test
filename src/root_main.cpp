#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <client/commitClient.hpp>
#include <helper/ip_tools.hpp>
#include <server/peersServer.hpp>
#include <server/syncServer.hpp>
#include <strage/strage.hpp>

#include <endpoint.pb.h>

using Block = sync::protocol::Block;
constexpr uint64_t mod = 1000000007;

int main() {
  std::cout << "---------------------------------- addPeer Server run!!  "
               "----------------------------------"
            << std::endl;
  std::thread addpeer_thread(peers::server::run);
  std::cout << "---------------------------------- sync Server run!! "
               "----------------------------------"
            << std::endl;
  std::thread sync_thread(sync::server::run);

  while (sync::strage::peers().empty())
    ;

  int pr = 0;
  for (int i = 0; i < 1000; i++) {
    Block block;
    block.set_id(i);
    block.set_creator(helper::getMyIp());
    block.set_context("context!! " + std::to_string(i));
    block.set_hash(((pr + i) % mod));
    pr += i;
    pr %= mod;

    sync::strage::strage().emplace_back(block);
    std::cout << i << "-th block send!!" << std::endl;
    commit::client::commit(sync::strage::strage().at(i));

    // wait 1 sec
    std::chrono::milliseconds wait(1000);
    std::this_thread::sleep_for(wait);
  }

  addpeer_thread.join();
  sync_thread.join();
}