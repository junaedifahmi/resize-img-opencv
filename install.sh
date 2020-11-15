# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip
# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
unzip opencv.zip
# Create build directory
mkdir -p build && cd build
# Configure
cmake  ../opencv-master
# Build
sudo cmake --build .

# Build Boost 
sudo apt-get install libboost-all-dev -y

cd ../..
mkdir -p include && cd include
git clone https://github.com/RonnyldoSilva/OpenCV_Mat_to_Base64.git