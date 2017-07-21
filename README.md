# Grpc + flatbuffers + Streaming Connection test ( alike Sync )

## prepare
```
cd docker
docker build -t satellitex/flatbuf-test .
cd ../
docker run -it --name flat-test -v $(pwd):/opt/flat-test satellitex/flatbuf-test /bin/bash
```


## build
```
mkdir buid
cd build
cmake ..
make
```