#ifndef IMAGE_HPP
#define IMAGE_HPP

#include<string>
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

using namespace std;

class Image{
private:

    static const int MAX_WIDTH = 1920;
    static const int MAX_HEIGHT = 1920;

    int width , height;

    int data[MAX_WIDTH * MAX_HEIGHT];

public:
    Image() : width(0) , height(0){};

    Image(int widthIn , int heightIn) : width(widthIn) , height(heightIn){}

    void imageInit(string fileName);

    int getWidth();

    int getHeight();

    int pixelGet(int row , int column);

    void pixelSet(int row , int column , int value);
};

#endif