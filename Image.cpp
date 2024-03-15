#include "Image.hpp"

#include<fstream>
#include<cassert>

using namespace std;

void Image::imageInit(string fileName) {
    ifstream is(fileName, ios::binary); // Open file in binary mode

    string tempStr;
    is >> tempStr;
    assert(tempStr == "P6"); // Check for P6 magic number
    is >> width;
    is >> height;
    is >> tempStr;
    assert(tempStr == "255");

    // Consume the newline character after the max value
    char newline;
    is.get(newline);

    // Allocate memory for the pixel data
    vector<unsigned char> pixels(width * height * 3); // 3 bytes per pixel (RGB)

    // Read pixel data directly into the vector
    is.read(reinterpret_cast<char*>(pixels.data()), pixels.size());

    // Close the file
    is.close();

    // Convert RGB values to grayscale and set pixels
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3; // Index in the pixels vector
            int r = pixels[index];           // Red component
            int g = pixels[index + 1];       // Green component
            int b = pixels[index + 2];       // Blue component
            pixelSet(i, j, (r + g + b) / 3); // Grayscale value
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