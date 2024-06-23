#pragma once

#define M_PI 3.14159265358979323846
#include "utils/vector3d.h"
#include <cmath>

using namespace std;

namespace matrices {
    Matrix rotate_x(double phi);

    Matrix rotate_y(double phi);

    Matrix rotate_z(double phi);

    Matrix scale(double scale);

    void toPolar(const Vector3D &point, double &theta, double &phi, double &r);

    Matrix translate(const Vector3D &vector);

    Matrix eyePointTrans(const Vector3D &eyepoint);
}