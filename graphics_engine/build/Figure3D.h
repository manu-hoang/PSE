#ifndef ENGINE_CC_FIGURE3D_H
#define ENGINE_CC_FIGURE3D_H

#include <vector>
#include <list>

#include "utils/vector3d.h"
#include "utils/easy_image.h"

using namespace std;
using namespace img;

class Face {
public:
    // De indexen refereren naar punten in de ‘points’ vector van de Figure-klasse
    vector<int> point_indexes;
};

/*
    * A 3-dimensional figure is described by the following:
    *      a number of points
    *      a number of planes (described by 2 or more points)
    *      a color
*/
class Figure {
public:
    vector<Vector3D> points;
    vector<Face> faces;
    Color color;

    Figure();

    // Function to apply the aforementioned transformations
    // all transformations can be applied at the same time: T * Rx * Ry * Rz * ...
    void applyTransformation(const Matrix &m);

    void triangulate();
};

// Apply transformation to a list of Figures
typedef list<Figure> Figures3D;

void applyTransformationAll(Figures3D &figs, const Matrix &m);

#endif //ENGINE_CC_FIGURE3D_H
