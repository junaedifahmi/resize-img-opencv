#include <iostream>
#include <boost/asio.hpp>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "process.cpp"
#include <opencv2/opencv.hpp>

#define EOS "EOS"

using namespace boost::asio;
using namespace std;
using ip::tcp;
using boost::asio::local::stream_protocol;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

void usage();
void handler(const boost::system::error_code& error, std::size_t byte_transfered);

int main(int argc, char const *argv[]){
    if (argc < 4){
        usage();
        exit(1);
    }
    // Take IP Adress 
    std::string ip = argv[1];
    int port = atoi(argv[2]);
    

    // Load the original image
    std::string path = argv[3];
    int w = atoi(argv[4]);
    int h = atoi(argv[5]);

    cv::Mat img = cv::imread(path, CV_LOAD_IMAGE_COLOR);
    std::string img_s = encode_64(img);

    // Make to json
    ptree pt;
    pt.put("input_jpeg", img_s);
    pt.put("desired_width", w);
    pt.put("desired_height", h);

    // Audio file reading 
    std::ostringstream buf;
    write_json(buf, pt, false);
    std::string json = buf.str();

    // Create service
    boost::asio::io_service service;
    tcp::socket socket_(service);
    tcp::endpoint ep(boost::asio::ip::address::from_string(ip), port);
    
    socket_.connect(ep);
    std::cout << "Service Ready" << std::endl ;

    // Send data
    boost::asio::write(socket_, boost::asio::buffer(json));
    boost::asio::write(socket_, boost::asio::buffer(EOS));

    std::cout << "Image SENT" << std::endl ;
    // receive and print result
    boost::system::error_code error;

    boost::asio::streambuf receivemsg;
    boost::asio::read(socket_, receivemsg, boost::asio::transfer_all(), error);
    if(error && error != boost::asio::error::eof){
        std::cout << "Receve failed"     << std::endl;
    } else {
        auto trans = boost::asio::buffer_cast<const char*>(receivemsg.data());
        std::cout << trans << endl;
    }

    return 0;
}

void usage(void){
    std::cerr << "Usage w2lClient <ip> <port> <file>" << std::endl;
}

void handler(const boost::system::error_code& error, std::size_t byte_transfered){
    std::cout << "[ "<< error.value() << " ]" << byte_transfered << "had transfered" << std::endl ;
}