cmake_minimum_required(VERSION 3.14)
project(NodeFluxTest)
#include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Declare the executable target built from your sources
#add_executable(server src/server.cpp)
#add_executable(client src/client.cpp)
add_executable(NodeFluxServer src/nserver.cpp)
add_executable(NodeFluxClient src/nclient.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/OpenCV_Mat_to_Base64)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)

#target_link_libraries(server PRIVATE ${OpenCV_LIBS} libpthread.so.0)
#target_link_libraries(server PRIVATE ${Boost_LIBS})

#target_link_libraries(client PRIVATE ${OpenCV_LIBS} libpthread.so.0)
#target_link_libraries(client PRIVATE ${Boost})

target_link_libraries(NodeFluxServer PRIVATE ${Boost_LIBS} libpthread.so.0 ${OpenCV_LIBS}) 
target_link_libraries(NodeFluxClient PRIVATE ${Boost_LIBS} libpthread.so.0 ${OpenCV_LIBS})

