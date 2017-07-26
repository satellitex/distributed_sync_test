#include <string>
#include <vector>
#include <thread>

#include <server/commitServer.hpp>
#include <server/syncServer.hpp>
#include <client/peersClient.hpp>
#include <helper/ip_tools.hpp>

int main(){
  std::cout << "---------------------------------- commit Server run!! ----------------------------------" << std::endl;
  std::thread commit_thread(commit::server::run);

  auto ip = helper::getRootIp();
  std::cout << "addPeer!! " << ip << std::endl;
  peers::client::PeersClient client(ip);
  client.addPeer();

  commit_thread.join();
}