#define _USE_MATH_DEFINES
#include "createSolids.h"
#include <algorithm>
#include <fstream>
#include <stack>
#include "Matrices.h"

Figure createCube() {
    Figure figure;

    vector<vector<double>> points = {
            {1, -1, -1}, {-1, 1, -1}, {1, 1, 1}, {-1, -1, 1},
            {1, 1, -1}, {-1, -1, -1}, {1, -1, 1}, {-1, 1, 1}
    };

    // We push back blank point so that we can refer to the point indices easier
    Vector3D center_point = Vector3D::point(0,0,0);
    figure.points.push_back(center_point);

    for(auto &point : points){
        Vector3D homogene_point = Vector3D::point(point[0], point[1], point[2]);
        figure.points.push_back(homogene_point);
    }

    vector<vector<int>> faces = {
            {1, 5, 3, 7}, {5, 2, 8, 3}, {2, 6, 4, 8},
            {6, 1, 7, 4}, {7, 3, 8, 4}, {1, 6, 2, 5}
    };

    for (auto &face : faces) {
        Face new_face;
        for(auto &point : face){
            new_face.point_indexes.push_back(point);
        }
        figure.faces.push_back(new_face);
    }

    return figure;
}

Figure createTetrahedron() {
    Figure figure;

    vector<vector<double>> points = {
            {1, -1, -1}, {-1, 1, -1},
            {1, 1, 1}, {-1, -1, 1}
    };

    // We push back blank point so that we can refer to the point indices easier
    Vector3D center_point = Vector3D::point(0,0,0);
    figure.points.push_back(center_point);

    for(auto &point : points){
        Vector3D homogene_point = Vector3D::point(point[0], point[1], point[2]);
        figure.points.push_back(homogene_point);
    }

    vector<vector<int>> faces = {
            {1, 2, 3}, {2, 4, 3},
            {1, 4, 2}, {1, 3, 4}
    };

    for (auto &face : faces) {
        Face new_face;
        for(auto &point : face){
            new_face.point_indexes.push_back(point);
        }
        figure.faces.push_back(new_face);
    }
    return figure;
}