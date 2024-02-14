#include<string>
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

using namespace std;

class Image(){
private:
    int width , height;

    int data[1280 * 1280];

public:

    void imageInit(string fileName);

    void pixelGet(int row , int column);

    void pixelSet(int row , int column);
}

Image::void imageInit(string fileName){

    ifstream is(fileName);

    string tempStr;
    is >> tempStr;
    assert(tempStr == "P3");
    is >> width;
    is >> height;
    is >> tempStr;
    assert(tempStr == "255");

    int r , g , b; 

    for(int r = 0 ; r < height ; r++){
        for(int c = 0 ; c < width ; c++){
        is >> r >> g >> b;
        pixelSet(r , c , (r + g + b) / 3);
    }
  }
}

Image::void pixelSet(int row , int column , int value){
    data[column + (row * width)] = value;
}
Image::int pixelGet(int row , int column){
    return (data[column + (row * width)]);
}