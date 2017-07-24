#ifndef DISTRIBUTED_SYNC_COMMITSERVER_HPP
#define DISTRIBUTED_SYNC_COMMITSERVER_HPP

#include <helper/ip_tools.hpp>

#include <endpoint.pb.h>
#include <endpoint.grpc.pb.h>

#include <grpc++/grpc++.h>


namespace commit {
  namespace server {

    using grpc::Server;
    using grpc::ServerAsyncResponseWriter;
    using grpc::ServerBuilder;
    using grpc::ServerContext;
    using grpc::ServerCompletionQueue;
    using grpc::Status;

    using sync::protocol::Block;
    using sync::protocol::Commit;
    using sync::protocol::CommitResponse;

    void run();

    class CommitServer {
     public:
      ~CommitServer();
      void Run();

     private:
      class CallData {
       public:
        CallData( Commit::AsyncService* service, ServerCompletionQueue* cq );

        void Proceed();

       private:
        Commit::AsyncService* service_;
        ServerCompletionQueue* cq_;
        ServerContext ctx_;
        Block block_;
        CommitResponse response_;
        ServerAsyncResponseWriter<CommitResponse> responder_;

        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;
      };

      void HandleRpcs();

      std::unique_ptr<ServerCompletionQueue> cq_;
      Commit::AsyncService service_;
      std::unique_ptr<Server> server_;
    };
  }
}

#endif  // DISTRIBUTED_SYNC_COMMITSERVER_HPP
