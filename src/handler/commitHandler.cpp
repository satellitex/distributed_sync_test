
#include <client/syncClient.hpp>
#include <handler/commitHandler.hpp>
#include <strage/strage.hpp>
#include <strage/validator.hpp>

namespace commit {
  namespace handler {
    void handle(const Block& block) {
      static thread sync_thread_;

      if (sync::strage::validate(block)) {
        sync::strage::strage().emplace_back(block);
        if (sync::strage::status().unsynced()) {
          sync::strage::status().activate();
          // TODO send activate tx
        } else {
          if (sync::strage::status().synced()) {
            sync::strage::status().stop();
            // TODO send stop tx
          } else {
            if( !sync_thread_.joinable() ) {
              sync_thread_ = [&]() {
                sync::client::SyncClient client;
                auto ip = block.ip();
                client.fetchBlocks(ip, sync::strage::strage().size());
              };
            }
          }
        }
      }

    }
  }
}
