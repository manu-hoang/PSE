#define _USE_MATH_DEFINES
#include "Lines2D.h"
#include "cmath"
#include <limits>
#include "utils/easy_image.h"


using namespace std;

// scale lines with factor d
Lines2D scaleLines(Lines2D &lines, double d ){
    for( auto &line : lines){
        line.p1.x = line.p1.x * d;
        line.p1.y = line.p1.y * d;

        line.p2.x = line.p2.x * d;
        line.p2.y = line.p2.y * d;
    }
    return lines;
}

// add lines with dx,dy
Lines2D addDLines(Lines2D &lines, double dx, double dy){
    for( auto &line : lines){
        line.p1.x = line.p1.x + dx;

        line.p1.y = line.p1.y + dy;

        line.p2.x = line.p2.x + dx;

        line.p2.y = line.p2.y + dy;
    }
    return lines;
}

// round all lines to int
Lines2D roundLines(Lines2D &lines){
    for( auto &line : lines){
        line.p1.x = lround(line.p1.x);

        line.p1.y = lround(line.p1.y);

        line.p2.x = lround(line.p2.x);

        line.p2.y = lround(line.p2.y);
    }
    return lines;
}

img::EasyImage draw2DLines(Lines2D &lines, int size, vector<double> background_color){
    // calculate extrema values
    double x_min = std::numeric_limits<double>::max();
    double x_max = std::numeric_limits<double>::min();

    double y_min = std::numeric_limits<double>::max();
    double y_max = std::numeric_limits<double>::min();

    // Calculate min / max coordinates of image
    for(const auto& line : lines) {
        for (const auto& point : {line.p1, line.p2}) {
            if (point.x < x_min) x_min = point.x;
            if (point.x > x_max) x_max = point.x;
            if (point.y < y_min) y_min = point.y;
            if (point.y > y_max) y_max = point.y;
        }
    }
    // calculate input x and y ranges
    double x_range = x_max - x_min;
    double y_range = y_max - y_min;

    // calculate output image size
    double image_x = size * (x_range / fmax(x_range,y_range) );
    double image_y = size * (y_range / fmax(x_range,y_range) );

    // calculate scale factor d
    double d = 0.95 * (image_x / x_range);

    // scale lines by d
    lines = scaleLines(lines, d);

    // calculate DC and d of x and y
    double DCx = d * (x_min + x_max)/2;
    double DCy = d * (y_min + y_max)/2;

    double dx = image_x/2 - DCx;
    double dy = image_y/2 - DCy;

    // add (dx,dy) to all coordinates
    lines = addDLines(lines, dx, dy);

    // round all lines
    lines = roundLines(lines);

    // -------------------------------------------- //
    //              Generate image                  //
    // -------------------------------------------  //

    // set background color
    img::Color background = img::Color(lround(background_color[0] * 255), lround(background_color[1] * 255), lround(background_color[2] * 255));

    // image constructor
    img::EasyImage image(lround(image_x), lround(image_y), background);

    // draw every line in Lines2D lines
    for (auto line : lines){
        image.draw_line(lround(line.p1.x), lround(line.p1.y), lround(line.p2.x), lround(line.p2.y), line.color);
    }

    return image;
}

Point2D project_point (const Vector3D &point3d, const double d){
    Point2D point2d;

    double x = (d * point3d.x) / (-point3d.z);
    double y = (d * point3d.y) / (-point3d.z);

    point2d.x = x;
    point2d.y = y;
    point2d.z = point3d.z;

    return point2d;
}

Lines2D doProjection(const Figures3D &figures, double d){
    Lines2D output;

    for(auto &figure : figures){
        for(auto &face : figure.faces){

            // Map all the indexes to the points
            vector<Vector3D> to_project;
            for(auto &index : face.point_indexes){
                to_project.push_back(figure.points[index]);
            }

            vector<Point2D> projected_points;
            for(auto &point : to_project){
                auto projected_point = project_point(point, d);
                projected_points.push_back(projected_point);
            }

            for (long long unsigned int i = 0; i < projected_points.size()-1; ++i) {
                Line2D line = Line2D(projected_points[i],projected_points[i+1]);

                line.z1 = projected_points[i].z;
                line.z2 = projected_points[i+1].z;
                line.color = figure.color;

                output.push_back(line);
            }

            // Final line: ending point to starting point
            Line2D line = Line2D(projected_points[projected_points.size()-1],projected_points[0]);

            line.z1 = projected_points[projected_points.size()-1].z;
            line.z2 = projected_points[0].z;
            line.color = figure.color;

            output.push_back(line);

        }
    }

    return output;
}
