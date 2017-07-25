#include <string>
#include <vector>
#include <thread>

#include <server/syncServer.hpp>
#include <client/syncClient.hpp>

int main(){

  std::cout << "---------------------------------- commit Server run!! ----------------------------------" << std::endl;
  std::thread commit_thread(commit::server::run);

  std::cout << "---------------------------------- sync Server run!! ----------------------------------" << std::endl;
  std::thread sync_thread(sync::server::run);

  commit_thread.join();
  sync_thread.join();

}