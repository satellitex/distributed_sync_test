# Distributed Synchornization System Test ( Use Grpc + protoc-buffer + Streaming Connection )

## prepare
```
cd docker
docker build -t satellitex/distributed-sync-test .
cd ../
docker run -it --name dsync -v $(pwd):/opt/distributed_sync_test satellitex/distributed-sync-test /bin/bash
```


## build
```
mkdir buid
cd build
cmake ..
make
```