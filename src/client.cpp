#include <helper/ip_tools.hpp>
#include <client/syncClient.hpp>
#include <iostream>


int main() {
  std::cout << "start test distributed!!" << std::endl;

  std::cout << helper::getMyIp() << std::endl;
}