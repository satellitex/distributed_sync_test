# Distributed Synchornization System Test ( Use Grpc + protoc-buffer + Streaming Connection )

## prepare
```
cd docker
docker build -t satellitex/distributed-sync-test .
cd ../
docker run -it --name dsync -v $(pwd):/opt/dsync satellitex/distributed-sync-test /bin/bash
```


## build
```
mkdir buid
cd build
cmake ..
make
```

### run unit test
#### one side
```
./bin/root-main
```
#### another side
```
./bin/child-main
```
After N sec
```
Ctrl-C
```
After N sec
```
./bin/child-main
```


