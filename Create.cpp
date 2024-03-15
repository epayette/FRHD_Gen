#include "Track.hpp"
#include "Image.hpp"

#include<string>
#include<iostream>
#include<cmath>

using namespace std;

int main(){   

    Track * ride = new Track();
    Image * img = new Image();

    img->imageInit("FRHDBridgeTest.ppm");
    ride->addImage(img , -2000 , 100);
    ride->updateFile("track.txt");

    delete ride;
    delete img;
    return 0;
}