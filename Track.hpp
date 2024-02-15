#include<string>
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

using namespace std;

class Track {
private:
    string dark, light;

    void addPixel(int pixelVal , int startX , int startY , int curX , int curY);

    int customRound(double input , vector<double> values);

    string convertNum(int num); // shorten with do-while
    string convertCoord(vector<int> coords);    // change to include multiple inputs

public:

    Track(){};

    void addDark(vector<int> coords);
    void addLight(vector<int> coords);

    void updateFile(string fileName);

    void addPixel(int pixelVal , int x , int y);

    void addImage(*Image img , int startX , int startY);
};