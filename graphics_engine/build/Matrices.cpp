#include "Matrices.h"

Matrix matrices::rotate_x(double phi) {
    Matrix matrix;

    // convert to radians
    phi *= M_PI/180;
    matrix(2,2) = cos(phi);
    matrix(2,3) = sin(phi);
    matrix(3,2) = -sin(phi);
    matrix(3,3) = cos(phi);
    return matrix;
}

Matrix matrices::rotate_y(double phi) {
    Matrix matrix;

    // convert to radians
    phi *= M_PI/180;
    matrix(1,1) = cos(phi);
    matrix(3,1) = sin(phi);
    matrix(1,3) = -sin(phi);
    matrix(3,3) = cos(phi);
    return matrix;
}

Matrix matrices::rotate_z(double phi) {
    Matrix matrix;

    // convert to radians
    phi *= M_PI/180;
    matrix(1,1) = cos(phi);
    matrix(1,2) = sin(phi);
    matrix(2,1) = -sin(phi);
    matrix(2,2) = cos(phi);
    return matrix;
}

Matrix matrices::scale(double scale) {
    Matrix matrix;

    matrix(1,1) = scale;
    matrix(2,2) = scale;
    matrix(3,3) = scale;

    return matrix;
}

void matrices::toPolar(const Vector3D &point, double &theta, double &phi, double &r) {
    // calculate r
    r = sqrt(pow(point.x,2) + pow(point.y,2) + pow(point.z,2));

    // calculate theta (in radians)
    theta = atan2(point.y,point.x);

    // calculate phi (in radians)
    phi = acos(point.z / r);
}

Matrix matrices::translate(const Vector3D &vector) {
    Matrix matrix;
    matrix(4,1) = vector.x;
    matrix(4,2) = vector.y;
    matrix(4,3) = vector.z;
    return matrix;
}

Matrix matrices::eyePointTrans(const Vector3D &eyepoint) {

    // (θ, φ, r)
    double theta;
    double phi;
    double r;

    Matrix matrix;

    toPolar(eyepoint, theta, phi, r);

    matrix(1, 1) = -sin(theta);
    matrix(1,2) = -cos(theta) * cos(phi);
    matrix(1,3) = cos(theta) * sin(phi);

    matrix(2,1) = cos(theta);
    matrix(2,2) = -sin(theta) * cos(phi);
    matrix(2,3) = sin(theta) * sin(phi);

    matrix(3,2) = sin(phi);
    matrix(3,3) = cos(phi);

    matrix(4,3) = -r;

    return matrix;
}
