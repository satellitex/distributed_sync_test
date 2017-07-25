#include <grpc/support/log.h>
#include <server/commitServer.hpp>
#include <strage/strage.hpp>

namespace commit {
  namespace server {

    void run(){
      CommitServer server;
      server.Run();
    }

    CommitServer::~CommitServer() {
      server_->Shutdown();
      cq_->Shutdown();
    }

    void CommitServer::Run() {
      std::string server_address(helper::getMyIp() + ":50051");

      ServerBuilder builder;
      builder.AddListeningPort(server_address,
                               grpc::InsecureServerCredentials());
      builder.RegisterService(&service_);
      cq_ = builder.AddCompletionQueue();
      server_ = builder.BuildAndStart();
      std::cout << "Server listening on " << server_address << std::endl;

      HandleRpcs();
    }

    CommitServer::CallData::CallData(Commit::AsyncService *service,
                                     ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
      Proceed();
    }

    void CommitServer::CallData::Proceed() {
      if (status_ == CREATE) {
        status_ = PROCESS;

        service_->RequestcommitBlock(&ctx_, &block_, &responder_, cq_, cq_,
                                     this);


        std::cout << "CallData CREATE" << std::endl;

      } else if (status_ == PROCESS) {
        new CallData(service_, cq_);

        std::cout << "CallData PROCESS" << std::endl;
        std::cout << "id: " << block_.id() << std::endl;
        sync::strage::strage().emplace_back( block_ );

        response_.set_status(CommitResponse::SUCCESS);
        status_ = FINISH;
        responder_.Finish(response_, Status::OK, this);
      } else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
      }
    }

    void CommitServer::HandleRpcs() {
      new CallData(&service_, cq_.get());
      void *tag;
      bool ok;
      while (true) {
        GPR_ASSERT(cq_->Next(&tag, &ok));
        GPR_ASSERT(ok);
        static_cast<CallData *>(tag)->Proceed();
      }
    }
  }
}