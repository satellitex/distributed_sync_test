#include <helper/ip_tools.hpp>
#include <string>

#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

namespace helper {
  std::string getMyIp() {
    std::string interface = "eth0";  // TODO : temporary "eth0"

    int sockfd;
    struct ifreq ifr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, interface.c_str(), IFNAMSIZ - 1);
    ioctl(sockfd, SIOCGIFADDR, &ifr);
    close(sockfd);
    return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
  }
  std::string getRootIp() {
    try {
      std::string path = std::getenv("SYNC_PATH");
      std::cout << path << std::endl;

      std::ifstream fin(path + "/config/root.txt");
      std::string ip;
      fin >> ip;
      return ip;
    } catch (...) {
      std::cout << "can't setting config." << std::endl;
      std::cout << "please write root ip to `config/root.txt`" << std::endl;
      return getMyIp();
    }
  }
}