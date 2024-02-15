#include<string>
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

using namespace std;

class Image(){
private:
    int width , height;

    int data[width * height];

public:
    Image(int widthIn , int heightIn) : width(widthIn) , height(heightIn){}

    void imageInit(string fileName);

    int getWidth();

    int getLength();

    int pixelGet(int row , int column);

    void pixelSet(int row , int column , int value);
}