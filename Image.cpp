#include "Image.hpp"

#include<fstream>
#include<cassert>

using namespace std;

void Image::imageInit(string fileName){

    ifstream is(fileName);

    string tempStr;
    is >> tempStr;
    assert(tempStr == "P3");
    is >> width;
    is >> height;
    is >> tempStr;
    assert(tempStr == "255");

    int r , g , b; 

    for(int row = 0 ; row < height ; row++){
        for(int col = 0 ; col < width ; col++){
        is >> r >> g >> b;
        pixelSet(row , col , (r + g + b) / 3);
    }
  }
}
int Image::getWidth(){
    return width;
}
int Image::getHeight(){
    return height;
}
void Image::pixelSet(int row , int column , int value){
    data[column + (row * width)] = value;
}
int Image::pixelGet(int row , int column){
    return (data[column + (row * width)]);
}