#include<string>
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

using namespace std;

class Track {
private:

    string dark, light, fullTrack;

    void printPixel(int pixelVal , int startX , int startY , int curX , int curY);

    int customRound(double input , vector<double> values);

    string convertNum(int num); // shorten with do-while
    string convertCoord(vector<int> coords);    // change to include multiple inputs

public:

    Track(){};

    void addDark(vector<int> coords);
    void addLight(vector<int> coords);

    void addPic(double value);

    void updateFile(string fileName);
};

void Track::printPixel(int pixelVal , int startX , int startY , int curX , int curY){

    switch(customRound(pixelVal , {255.0 , 242.3 , 195.5 , 174.3 , 140.25 , 95.2 , 45.9 , 12.8})){
        case 0:
            vector<int> A = {startX + curX};
            break;
        case 1:

            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 0:
            break;
    }
}

int Track::customRound(double input , vector<double> values){   // outputs index of nearest value to input
    int outCase;
    int smallestDist = 255;

    for(int i = values.size() ; i >= 0 ; i--){
        if(smallestDist > abs(input - values[i])){
            outCase = i;
            smallestDist = abs(input - values[i]);
        }
    }
    return outCase;
}

string Track::convertNum(int num){  // converts decimal int to base 32 string

    string ref = "0123456789abcdefghijklmnopqrstuv";
    string out, sign;

    int save = num;

    if (save < 0) {
        sign.append("-");
        save *= -1;
    }
    else if(save == 0){
        return "0";
    }
    while (save != 0){
        out.insert(0,1,ref[save % 32]);

        save -= save % 32;
        save /= 32;
    }
    sign += out;
    return sign;
}

string Track::convertCoord(vector<int> coords){ // takes two decimal coordinates, and converts to base 32 string

    if(coords.size() != 4){
        cout << "coords must have four values" << endl;
        exit(1);
    }

    string out;

    for(int i=0 ; i<4 ; i++){
        out.append(convertNum(coords[i]));
        out.append(" ");
    }
    out.pop_back();
    out.append(",");

    return out;
}

void Track::addDark(vector<int> coords){   // takes decimal coords, adds base 32 coords to private dark string
    dark.append(convertCoord(coords));
}

void Track::addLight(vector<int> coords){   // takes decimal coords, adds base 32 coords to private light string
    light.append(convertCoord(coords));
}

void Track::updateFile(string fileName){    // appends dark and light strings, then writes to file
    ofstream trackFile(fileName.c_str());

    if(dark.size() > 0){
    dark.replace(dark.size() - 1, 1, "#");
    } else{
        dark += "#";
    }
    if(light.size() > 0){
    light.replace(light.size() - 1, 1, "#");
    } else{
        light += "#";
    }
    string finalOut = dark + light;

    trackFile << finalOut;
}

void Track::addPic(double value){   // ...
    cout << customRound(value , {255.0 , 242.3 , 195.5 , 174.3 , 140.25 , 95.2 , 45.9 , 12.8}) << endl;
}