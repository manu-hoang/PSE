#ifndef ENGINE_CC_INPUT_TYPE_H
#define ENGINE_CC_INPUT_TYPE_H

#include <iostream>
#include <string>

#include "utils/easy_image.h"
#include "utils/ini_configuration.h"

#include "Figure3D.h"
#include "Lines2D.h"
#include "createSolids.h"
#include "Matrices.h"
#include "ZBuffer.h"

using namespace std;

img::EasyImage DrawWireframe(const ini::Configuration &configuration){
    img::EasyImage image;

    int size = configuration["General"]["size"].as_int_or_die();
    vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();
    vector<double> backgroundcolor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();

    // [3D Line drawings] [Figure[i]]
    Figures3D figures;
    for (int i = 0; i < nrFigures; ++i) {
        Figure figure;

        string figure_it = "Figure";
        figure_it += to_string(i);

        string FigureType = configuration[figure_it]["type"].as_string_or_die();

        double rotateX = configuration[figure_it]["rotateX"].as_double_or_die();
        double rotateY = configuration[figure_it]["rotateY"].as_double_or_die();
        double rotateZ = configuration[figure_it]["rotateZ"].as_double_or_die();
        double scale = configuration[figure_it]["scale"].as_double_or_die();

        vector<double> center = configuration[figure_it]["center"].as_double_tuple_or_die();
        vector<double> color = configuration[figure_it]["color"].as_double_tuple_or_die();

        if(FigureType == "Cube"){
            figure = createCube();
        }

        else if(FigureType == "Tetrahedron"){
            figure = createTetrahedron();
        }

        figure.color = Color(lround(color[0] * 255), lround(color[1] * 255), lround(color[2] * 255));

        Vector3D translation_vector = Vector3D::vector(center[0],center[1],center[2]);

        Matrix translation_matrix = matrices::translate(translation_vector);
        Matrix scale_factor = matrices::scale(scale);
        Matrix rotate_x = matrices::rotate_x(rotateX);
        Matrix rotate_y = matrices::rotate_y(rotateY);
        Matrix rotate_z = matrices::rotate_z(rotateZ);

        figure.applyTransformation(rotate_x * rotate_y * rotate_z * scale_factor * translation_matrix);

        figures.push_back(figure);
    }

    // -------------------------------------------- //
    //              Generate image                  //
    // -------------------------------------------  //

    // Calculate polar coordinates and corresponding eye point matrix
    Vector3D camera = Vector3D::point(eye[0], eye[1], eye[2]);
    Matrix eye_point = matrices::eyePointTrans(camera);

    // apply matrix
    applyTransformationAll(figures, eye_point);

    // generate Lines2D list
    Lines2D lines = doProjection(figures, 1);

    // draw image
    image = draw2DLines(lines, size, backgroundcolor);

    return image;
}


#endif //ENGINE_CC_INPUT_TYPE_H
