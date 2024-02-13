#include "function.hpp"

#include<string>
#include<iostream>
#include<cmath>

using namespace std;

int main(){   

    Track ride;

    for(int i = -100 ; i < 1000 ; i++){

    vector<int> A = {6 * i , static_cast<int>((160 * sin((6 * i) / 160.0)) + 100)
                    ,(6 * i) + 6 , static_cast<int>((160 * sin(((6 * i) + 6) / 160.0)) + 100)};

    ride.addDark(A);
    }
    for(int i = -1200 ; i < 6600 ; i+= 30){
        for(int j = -700 ; j < 700 ; j+= 30){
            vector<int> B = {i - 1 , j ,i + 1 , j};
            vector<int> C = {i , j - 1 , i , j + 1};

            ride.addLight(B);
            ride.addLight(C);
        }
    }

    ride.addPic(134.3);

    ride.updateFile("track.txt");
}