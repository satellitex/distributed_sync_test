#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include <client/commitClient.hpp>

#include <endpoint.grpc.pb.h>
#include <endpoint.pb.h>


using Block = sync::protocol::Block;
constexpr uint64_t mod = 1000000007;

int main() {

  commit::client::CommitClient client;
  Block block;
  int pr = 0;
  for(int i=0;i<100;i++) {
    block.set_id(i);
    block.set_context("context!! " + std::to_string(i));
    block.set_hash(((pr+i)%mod));

    std::cout << i << "-th block send!!" << std::endl;
    client.commit(block);

    pr += i;
    pr %= mod;

    //wait 1 sec
    std::chrono::milliseconds wait( 1000 );
    std::this_thread::sleep_for( wait );
  }

}