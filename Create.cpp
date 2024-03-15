#include "Track.hpp"
#include "Image.hpp"

#include<string>
#include<iostream>
#include<cmath>

using namespace std;

int main(){   

    Track * ride = new Track();
    Image * img = new Image();

    img->imageInit("FRHDTest.ppm");
    ride->addImage(img , 0 , 0);
    ride->updateFile("track.txt");

    delete ride;
    delete img;
    return 0;
}