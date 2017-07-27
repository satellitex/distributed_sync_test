
#include <client/syncClient.hpp>
#include <handler/commitHandler.hpp>
#include <helper/thread_pool.hpp>
#include <strage/strage.hpp>
#include <strage/validator.hpp>

#include <thread>

namespace commit {
  namespace handler {

    void handle(const Block& block) {
      static std::thread sync_thread_;

      std::cout << "Handler" << std::endl;

      if (sync::strage::validate(block)) {
        std::cout << "Activate!!" << std::endl;
        sync::strage::status().activate();
        sync::strage::strage().emplace_back(block);

        if (sync::strage::status().unsynced()) {
          std::cout << "send activate tx" << std::endl;
          // TODO send activate tx
        }

      } else {
        std::cout << "Stop!!" << std::endl;
        sync::strage::status().stop();
        if (sync::strage::status().synced()) {
          std::cout << "send stop tx" << std::endl;
          // TODO send stop tx
        }

        if (!sync_thread_.joinable()) {
          std::cout << "start SyncClient!!" << std::endl;

          helper::thread::pool().process(std::thread([block]() {
            auto creator = block.creator();
            sync::client::SyncClient client(creator);
            client.fetchBlocks(sync::strage::strage().size());
          }));
        }
      }
    }
  }
}
