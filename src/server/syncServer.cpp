#include <helper/ip_tools.hpp>
#include <server/syncServer.hpp>
#include <strage/strage.hpp>

#include <iostream>

namespace sync {
  namespace server {

    void run() {
      std::string server_address(helper::getMyIp() + ":50051");
      sync::server::SyncServer service;

      ::grpc::ServerBuilder builder;
      builder.AddListeningPort(server_address,
                               ::grpc::InsecureServerCredentials());
      builder.RegisterService(&service);
      std::unique_ptr<::grpc::Server> server(builder.BuildAndStart());
      std::cout << "Server listening on " << server_address << std::endl;
      server->Wait();
    }

    ::grpc::Status SyncServer::fetchBlocks(
        ::grpc::ServerContext* context, const Request* request,
        ::grpc::ServerWriter<Block>* writer) {
      auto offset = request->offset();

      std::cout << "receive:" << std::endl;
      std::cout << "offset: " << offset << std::endl;

      for (auto i = 0;; i++) {
        while (i >= sync::strage::strage().size())
          ;
        auto& bk = sync::strage::strage().at(i);
        std::cout << i << "-th block" << std::endl;
        std::cout << "id : " << bk.id() << std::endl;
        std::cout << "context : " << bk.context() << std::endl;
        writer->Write(sync::strage::strage().at(i));

        if (i > 100) break;
      }
      return ::grpc::Status::OK;
    }
  }
}