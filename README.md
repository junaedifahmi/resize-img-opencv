# Resize Image Using OpenCV
This is the example code and program for resizing image with the utility of OpenCV. To reporduce this repo, first of all you have to install the dependencies as shown in `install.sh`. You can just run in in terminal. After that you want to build the program like other cmake project. 

```bash
mkdir -p build && cd build
cmake ..
make -j 4
```


## What You'll found
In the src file, we will find `nserver.cpp` and `nclient.cpp` these are the code we used for the server and the client. 

## Usage 
This program using client-server side, to run the program first you must run the `NodeFluxServer` binary with the commad as follows:

```bash
build/NodeFluxServer <host> <port>
```

After the program is running, you can try to use the `NodeFluxClient` program to send your image and the desired size you want. This is the example:

```bash
build/NodeFluxClient <host> <port> <image path> <widht> <height>
```

## Docker
In this project we also provide Dockerfile for easy installation. To use this Dockefile you can follow this directions:
```bash
docker build -t imgresize:latest .
docker run --rm -p 8080:8080 --name imageresize imgresize
```

## Thanks:
* [RonnyldoSilva](https://github.com/RonnyldoSilva/OpenCV_Mat_to_Base64.git) for providing very simple yet powerfull base64 encoder.