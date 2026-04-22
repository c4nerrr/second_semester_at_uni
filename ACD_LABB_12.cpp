//
// Created by c4ner on 4/22/2026.
//
#include <iostream>
#include <cmath>
#include <cstdint>
using namespace std;

struct Point {
    int x;
    int y;
    int colorCode;
};



double getEuclideanDistance(const Point p1, const Point p2) {
    const double d = sqrt(pow((p2.y-p1.y),2.0) + pow((p2.x-p1.x),2.0));
    return d;
}
double getManhattanDistance(const Point p1, const Point p2) {
    const double d1 = fabs(p2.x-p1.x) + fabs(p2.y-p1.y);
    return d1;
}



void drawVoronoi(Point point[], const int size, const bool isManhattan) {
    constexpr uint8_t height = 25;
    constexpr uint8_t width = 80; //NOLINT
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double minDist = 1e9; int closestIndex = 0;
            for (int i = 0; i < size; i++) {
                Point currentPixel{};
                currentPixel.x = x;
                currentPixel.y = y;

                double currentDist = 0;
                if (isManhattan) {
                    currentDist = getManhattanDistance(currentPixel, point[i]);
                }
                else {
                    currentDist = getEuclideanDistance(currentPixel, point[i]);
                }
                if (currentDist < minDist) {
                    minDist = currentDist;
                    closestIndex = i;
                }

            }
            cout << "\033[" << point[closestIndex].colorCode << "m";
            if (x == point[closestIndex].x && y == point[closestIndex].y) {
                cout << "XX";
            }
            else {
                cout << "  ";
            }
        }
        cout << "\033[0m";
        cout << endl;
    }

}

int main() {
    Point point[5] = {{15,15, 41}, {35,5, 42}, {55,20,43}, {25,10, 44}, {65,10,46}};
    cout << "Euclidean Distance: " << endl;
    drawVoronoi(point, 5, false);
    cout << "\n\n";
    cout << "Manhattan Distance: " << endl;
    drawVoronoi(point, 5, true);


}