#include <helper/ip_tools.hpp>
#include <server/syncServer.hpp>
#include <strage/strage.hpp>

#include <iostream>
#include <thread>

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
        ::grpc::ServerContext* context,
        ::grpc::ServerReaderWriter<Block, Request>* stream) {
      Request request;
      stream->Read(&request);
      auto offset = request.offset();

      std::cout << "receive:" << std::endl;
      std::cout << "offset: " << offset << std::endl;

      bool end_flag = false;

      std::thread receiver([&stream,&end_flag]{
        Request request;
        while( stream->Read(&request) ){
          if( request.offset() == -1 ) break;
        }
        end_flag = true;
      });

      std::thread sender([&stream,offset,&end_flag]{

        for (auto i = offset;; i++) {
          while (i >= sync::strage::strage().size()){
            if(end_flag) break;
          }
          if(end_flag) break;
          auto& bk = sync::strage::strage().at(i);
          std::cout << i << "-th block" << std::endl;
          std::cout << "id : " << bk.id() << std::endl;
          std::cout << "context : " << bk.context() << std::endl;
          stream->Write(bk);
        }

      });


      receiver.join();
      sender.join();
      return ::grpc::Status::OK;
    }
  }
}