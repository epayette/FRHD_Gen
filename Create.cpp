#include "Track.hpp"
#include "Image.hpp"

#include<string>
#include<iostream>
#include<cmath>

using namespace std;

int main(){   

    Track * ride = new Track();
    Image * img = new Image();

    img->imageInit("FRHDAsianTest.ppm");
    ride->addEfficientImage(*img, -500, -500);
    //ride->addImage(img, -500, -500);
    ride->updateFile("test.out");

    delete ride;
    delete img;
    return 0;
}