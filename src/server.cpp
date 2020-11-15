#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "process.cpp"

#define EOS "EOS"

using namespace boost::asio;
using ip::tcp;

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


void usage();

int main(int argc, char const *argv[]){
    // Argument parser
    if (argc < 3) {
        usage();
        exit(1);
    }

    auto port = atoi(argv[1]);
    auto config = argv[2];

    while (true) {
        // Server definition
        boost::asio::io_service service;
        tcp::acceptor accept(service, tcp::endpoint(tcp::v4(), port));
        tcp::socket sock(service);
        std::cout << "Service ready" << std::endl;
        
        accept.accept(sock);
        // Read the request
        boost::asio::streambuf receivemsg;
        boost::asio::read_until(sock, receivemsg, EOS);
        std::cout << "Audio RECEIVED" << std::endl;
        ptree pt;
        std::istream is(&receivemsg);
        read_json(is, pt);

        std::string img_s = pt.get<std::string>("input_jpeg");
        int h = pt.get<int>("desired_width");
        int w = pt.get<int>("desired_height");

        ptree pt_res = resize(img_s, h, w);

        std::ostringstream buf;
        write_json(buf, pt_res, false);
        std::string respons = buf.str();
        std::cout << respons << std::endl;

        boost::system::error_code error; 
        boost::asio::write(sock, boost::asio::buffer(respons), error);
        if( !error ){
            std::cout << "Done" << std::endl;
        } else {
            std::cout << "Duar EROR" << std::endl;
        }
        accept.close();
    }

    return 0;
}

void usage(){
    std::cerr << "usage: w2lServer <port> <engineconfig>" << std::endl;
}