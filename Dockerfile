FROM ubuntu:18.04

RUN apt update && upgrade -y
RUN apt install wget unzip libboost-all-dev cmake g++ -y 

COPY . /workspace
WORKDIR /workspace


# Install opencv
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip \
    unzip opencv.zip
    # Create build directory
    cd opencv-master
    mkdir -p build && cd build
    # Configure
    cmake  ..
    # Build
    cmake --build .

# Download base64 external
RUN mkdir -p include && cd include && git clone https://github.com/RonnyldoSilva/OpenCV_Mat_to_Base64.git


# Run CMAKE
RUN cd /workspace \
    mkdir -p build && cd build \
    cmake ..
    make -j 4
    cd /workspace

EXPOSE 8080
CMD ["nserver", "0.0.0.0", "8080"]

