#include<string>
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

#include "Track.hpp"
#include "Image.hpp"

using namespace std;



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

void Track::addPixel(int pixelVal , int x , int y){

    vector<int> top = {x , y , x + 2 , y};
    vector<int> right = {x + 2 , y , x + 2 , y + 2};
    vector<int> left = {x , y , x , y + 2};
    vector<int> bottom = {x , y + 2 , x + 2 , y + 2};

    switch(customRound(pixelVal , {255.0 , 242.3 , 195.5 , 174.3 , 140.25 , 95.2 , 45.9 , 12.8})){
        case 0:
            break;
        case 1:
            addLight(top);
            break;
        case 2:
            addLight(top);
            addLight(left);
            break;
        case 3:
            addLight(top);
            addLight(left);
            addLight(right);
            addLight(bottom);
            break;
        case 4:
            addDark(top);
            break;
        case 5:
            addDark(top);
            addLight(bottom);
            break;
        case 6:
            addDark(top);
            addDark(left);
            break;
        case 7:
            addDark(top);
            addDark(left);
            addDark(right);
            addDark(bottom);
            break;
    }
}

void Track::addImage(Image * img , int startX , int startY){

    for (int r = 0 ; r < img->getHeight() ; r++){
        for (int c = 0 ; c < img->getWidth() ; c++){

            int val = img->pixelGet(r , c);

            addPixel(val , (3 * c) + startX , (3 * r) + startY);
        }
    }
}

bool Track::addEfficientPixel(int pixelVal, int segment){
    bool segs[8] = {false};
    switch(customRound(pixelVal , {255.0 , 242.3 , 195.5 , 174.3 , 140.25 , 95.2 , 45.9 , 12.8})){
        case 0:
            break;
        case 1:
            segs[0] = true;
            break;
        case 2:
            segs[0] = true;
            segs[3] = true;
            break;
        case 3:
            segs[0] = true;
            segs[1] = true;
            segs[2] = true;
            segs[3] = true;
            break;
        case 4:
            segs[4] = true;
            segs[0] = true;
            break;
        case 5:
            segs[4] = true;
            segs[2] = true;
            segs[0] = true;
            break;
        case 6:
            segs[4] = true;
            segs[0] = true;
            segs[7] = true;
            segs[3] = true;
            break;
        case 7:
            segs[4] = true;
            segs[0] = true;
            segs[5] = true;
            segs[1] = true;
            segs[6] = true;
            segs[2] = true;
            segs[7] = true;
            segs[3] = true;
            break;
    }
    return segs[segment];
}

void Track::addLeftStreak(Image & img, int startX, int startY, int segment, int row){

    int lineStart, lineEnd;
    int col = 0;

    while(col < img.getWidth()){
        // looking for start
        while(!addEfficientPixel(img.pixelGet(row, col), segment)){
            col++;
        }
        lineStart = col;

        //looking for end
        while(addEfficientPixel(img.pixelGet(row, col), segment) && col < img.getWidth()){
            col++;
        }
        lineEnd = col;
        vector<int> line = {startX + (lineStart * 3), startY, startX + (lineEnd * 3), startY};
        
        if(segment > 3){
            addDark(line);
        } else {
            addLight(line);
        }
    }
}

void Track::addDownStreak(Image & img, int startX, int startY, int segment, int col){

    int lineStart, lineEnd;
    int row = 0;

    while(row < img.getHeight()){
        lineStart = 0;
        lineEnd = 0;
        // looking for start
        while(!addEfficientPixel(img.pixelGet(row, col), segment)){
            row++;
        }
        lineStart = row;

        //looking for end
        while(addEfficientPixel(img.pixelGet(row, col), segment) && row < img.getHeight()){
            row++;
        }
        lineEnd = row;
        vector<int> line = {startX, startY + (lineStart * 3), startX, startY + (lineEnd * 3)};
        
        if(segment > 3){
            addDark(line);
        } else {
            addLight(line);
        }
    }
}

void Track::addEfficientImage(Image & img, int startX, int startY){

    for(int row = 0; row < img.getHeight() - 1; row++){
        addLeftStreak(img, startX, startY + (row*3), 0, row);
        addLeftStreak(img, startX, startY + (row*3) + 2, 2, row);
        addLeftStreak(img, startX, startY + (row*3), 4, row);
        addLeftStreak(img, startX, startY + (row*3) + 2, 6, row);
    }
    cout << endl;
    for(int col = 0; col < img.getWidth() - 1; col++){
        addDownStreak(img, startX + (col*3) + 2, startY, 1, col);
        addDownStreak(img, startX + (col*3), startY, 3, col);
        addDownStreak(img, startX + (col*3) + 2, startY, 5, col);
        addDownStreak(img, startX + (col*3), startY, 7, col);
    }
}
