#ifndef ENGINE_DRAW2DLINE_H
#define ENGINE_DRAW2DLINE_H
#include <list>
#include <vector>
#include <fstream>

#include "utils/easy_image.h"

#include "Figure3D.h"

using namespace std;

class Point2D{
public:
    double x;
    double y;
    double z;

    Point2D(){
        x = 0;
        y = 0;
        z = 0;
    }
};

class Line2D{
public:
    Point2D p1;
    Point2D p2;
    Color color;

    double z1;
    double z2;

    double xl;
    double xr;

    Line2D( Point2D P1, Point2D P2){
        p1 = P1;
        p2 = P2;
        z1 = 0;
        z2 = 0;
        xl = 0;
        xr = 0;
    }
};

// draw all lines in a Lines2D list
using Lines2D = list<Line2D>;


Lines2D scaleLines(Lines2D &lines, double d);
Lines2D addDLines(Lines2D &lines, double dx, double dy);
Lines2D roundLines(Lines2D &lines);

img::EasyImage draw2DLines(Lines2D &lines, int size, vector<double> background_color);

// Project a 3D point to a 2D point (based on d)
Point2D project_point (const Vector3D &point3d, double d);

// Project a 3D figure into a Lines2D list
Lines2D doProjection(const Figures3D &, double d);

#endif //ENGINE_DRAW2DLINE_H
