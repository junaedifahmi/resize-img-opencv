#include <stdio.h>
#include <string>
#include <exception>
#include <opencv2/opencv.hpp>
#include <boost/property_tree/ptree.hpp>

#include "ConvertImage.cpp"


using namespace cv;
using boost::property_tree::ptree;

ImagemConverter base64;

string encode_64(cv::Mat img){
    string img_s = base64.mat2str(img);
    return img_s;
}

cv::Mat decode_64(string img_s){
    cv::Mat des = base64.str2mat(img_s);
    return des;
}

std::string resize(string img_s, int w, int h){
    cv::Mat src = decode_64(img_s);
    cv::Mat des;
    cv::resize(src, des, cv::Size(w, h));
    string encoded = encode_64(des);
    return encoded;
}