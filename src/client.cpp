#include <client/syncClient.hpp>
#include <helper/ip_tools.hpp>
#include <iostream>


int main() {
  std::cout << "start test distributed!!" << std::endl;

  sync::client::SyncClient client;
  std::cout << "-------------- fetchBlocks --------------" << std::endl;
  client.fetchBlocks(helper::getMyIp(), 0);
}