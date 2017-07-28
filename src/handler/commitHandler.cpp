
#include <client/syncClient.hpp>
#include <handler/commitHandler.hpp>
#include <helper/thread_pool.hpp>
#include <strage/strage.hpp>
#include <strage/validator.hpp>

#include <thread>

namespace commit {
  namespace handler {

    void handle(const Block& block) {
      static bool synced = false;
      std::cout << "Handler" << std::endl;

      if (sync::strage::validate(block)) {
        if (sync::strage::status().unsynced()) {
          synced = false;
          std::cout << "send activate tx" << std::endl;
          // TODO send activate tx
        }

        std::cout << "Activate!!" << std::endl;
        sync::strage::status().activate();
        sync::strage::strage().emplace_back(block);
      } else {
        if (sync::strage::status().synced()) {
          std::cout << "send stop tx" << std::endl;
          // TODO send stop tx
        }

        std::cout << "Stop!!" << std::endl;
        sync::strage::status().stop();

        if (!synced) {
          std::cout << "start SyncClient!!" << std::endl;
          synced = true;
          // process async
          helper::thread::pool().process(
              std::thread(sync::client::blockDownload, block));
        }
      }
    }
  }
}
