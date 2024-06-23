#include "ZBuffer.h"
#include "iostream"
#include "limits"
#include <math.h>

using namespace std;

ZBuffer::ZBuffer(const int width, const int height) {
    double posInf = std::numeric_limits<double>::infinity();

    for (int i = 0; i < height; ++i) {
        vector<double> array;

        for (int j = 0; j < width; ++j) {
            array.push_back(posInf);
        }

        this->push_back(array);
    }
}

double ZBuffer::get(unsigned int x, unsigned int y) {
    int inverse_y = this->size() - y - 1;
    return (*this)[inverse_y][x];
}

void ZBuffer::set(unsigned int x, unsigned int y, double value) {
    int inverse_y = this->size() - y - 1;
    (*this)[inverse_y][x] = value;
}

void draw_zbuf_line(ZBuffer &buffer, EasyImage &image, unsigned int x0, unsigned int y0, double z0, unsigned int x1, unsigned int y1, double z1, const Color &color){
    if (x0 >= image.get_width() || y0 >= image.get_height() || x1 >= image.get_width() || y1 > image.get_height()) {
        std::stringstream ss;
        ss << "Drawing line from (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ") in image of width "
           << image.get_width() << " and height " << image.get_height();
        throw std::runtime_error(ss.str());
    }

    if (x0 == x1)
    {
        //special case for x0 == x1
        for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++)
        {
            unsigned int a = max(y0, y1) - min(y0, y1);
            double pixelnr = a - (i - min(y0, y1));
            double p = pixelnr/a;

            double zi;
            if(std::min(y0, y1) == y0){
                zi = p/z0 + (1-p)/z1;
            } else {
                zi = p/z1 + (1-p)/z0;
            }


            if(zi < buffer.get(x0,i)){
                buffer.set(x0,i, zi);
                (image)(x0, i) = color;
            }

        }
    }
    else if (y0 == y1)
    {
        //special case for y0 == y1
        for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); i++)
        {
            unsigned int a = max(x0, x1) - min(x0, x1);
            double pixelnr = (a-(i-min(x0, x1)));
            double p = pixelnr/a;

            double zi;
            if(std::min(x0, x1) == x0){
                zi = p/z0 + (1-p)/z1;
            } else {
                zi = p/z1 + (1-p)/z0;
            }

            if(zi < buffer.get(i,y0)) {
                buffer.set(i,y0,zi);
                (image)(i, y0) = color;
            }
        }
    }
    else
    {
        bool swap = false;
        if (x0 > x1)
        {
            //flip points if x1>x0: we want x0 to have the lowest value
            std::swap(x0, x1);
            std::swap(y0, y1);
            swap = true;
        }
        double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);

        if (-1.0 <= m && m <= 1.0)
        {
            for (unsigned int i = 0; i <= (x1 - x0); i++)
            {
                unsigned int a = x1 - x0;
                double pixelnr = a - i;
                double p = pixelnr/a;

                double zi;
                if(!swap){
                    zi = p/z0 + (1-p)/z1;
                } else {
                    zi = p/z1 + (1-p)/z0;
                }

                if(zi < buffer.get(x0+i, (unsigned int) round(y0 + m * i))){
                    buffer.set(x0+i, (unsigned int) round(y0 + m * i), zi);
                    (image)(x0 + i, (unsigned int) round(y0 + m * i)) = color;
                }
            }
        }
        else if (m > 1.0)
        {
            for (unsigned int i = 0; i <= (y1 - y0); i++)
            {
                unsigned int a = y1 - y0;
                double pixelnr = a - i;
                double p = pixelnr / a;

                double zi;
                if(!swap){
                    zi = p/z0 + (1-p)/z1;
                } else {
                    zi = p/z1 + (1-p)/z0;
                }

                if(zi < buffer.get((unsigned int) round(x0 + (i / m)), y0 + i)) {
                    buffer.set((unsigned int) round(x0 + (i / m)), y0 + i, zi);
                    (image)((unsigned int) round(x0 + (i / m)), y0 + i) = color;
                }
            }
        }
        else if (m < -1.0)
        {
            for (unsigned int i = 0; i <= (y0 - y1); i++)
            {
                unsigned int a = y0 - y1;
                double pixelnr = a - i;
                double p = pixelnr / a;

                double zi;
                if(!swap){
                    zi = p/z0 + (1-p)/z1;
                } else {
                    zi = p/z1 + (1-p)/z0;
                }

                if(zi < buffer.get((unsigned int) round(x0 - (i / m)), y0 - i)){
                    buffer.set((unsigned int) round(x0 - (i / m)), y0 - i, zi);
                    (image)((unsigned int) round(x0 - (i / m)), y0 - i) = color;
                }
            }

        }
    }
}

void draw_zbuf_triangle(ZBuffer &buffer, EasyImage &img, const Vector3D &A_3D, const Vector3D &B_3D, const Vector3D &C_3D,
                        double d, double dx, double dy, const Color& color) {

    double posInf = std::numeric_limits<double>::infinity();
    double negInf = - std::numeric_limits<double>::infinity();

    // project all 3d points into 2d points and add dx/dy
    Point2D A = project_point(A_3D, d);
    A.x += dx;
    A.y += dy;

    Point2D B = project_point(B_3D, d);
    B.x += dx;
    B.y += dy;

    Point2D C = project_point(C_3D, d);
    C.x += dx;
    C.y += dy;

    // Triangle
    vector<Line2D> lines;
    Line2D AB = Line2D(A,B);
    Line2D AC = Line2D(A,C);
    Line2D BC = Line2D(B,C);
    lines.push_back(AB); lines.push_back(AC); lines.push_back(BC);

    // Drawing from triangle Y min to Y max (vertically bottom to top)
    int y_min = lround(min(min(A.y, B.y), C.y) + 0.5);
    int y_max = lround(max(max(A.y, B.y), C.y) - 0.5);

    for (int yi = y_min; yi <= y_max; ++yi) {

        for(auto &line : lines){
            line.xl = posInf;
            line.xr = negInf;
        }

        for (auto &PQ : lines){

            // Test if yi is inbetween p1.y and p2.y
            if( ((yi - PQ.p1.y) * (yi - PQ.p2.y) <= 0) and (PQ.p1.x != PQ.p2.x and PQ.p1.y != PQ.p2.y)){

                // Xi = Xq + (Xp - Xq) * (Yi - Yq)/(Yp - Yq)
                double xi = PQ.p2.x + (PQ.p1.x - PQ.p2.x) * ((yi - PQ.p2.y) /
                                                            (PQ.p1.y - PQ.p2.y));
                PQ.xl = xi;
                PQ.xr = xi;
            }
        }

        int xl = lround(min(min(lines[0].xl, lines[1].xl), lines[2].xl) + 0.5);
        int xr = lround(max(max(lines[0].xr, lines[1].xr), lines[2].xr) - 0.5);

        // Z BUFFERING
        double xg = (A.x + B.x + C.x)/3;
        double yg = (A.y + B.y + C.y)/3;

        // 1/Z waarde van massa middelpunt
        double zg = 1/(3*A.z) + 1/(3*B.z) + 1/(3*C.z);

        Vector3D u = B_3D - A_3D;   // vector A -> B
        Vector3D v = C_3D - A_3D;   // vector A -> C

        // de vector w = (w1, w2, w3):
        // w1 = u2v3 − u3v2,
        // w2 = u3v1 − u1v3,
        // w3 = u1v2 − u2v1
        double w1 = u.y * v.z - u.z * v.y;
        double w2 = u.z * v.x - u.x * v.z;
        double w3 = u.x * v.y - u.y * v.x;

        // w1xA + w2yA + w3zA = k
        double k = w1 * A_3D.x + w2 * A_3D.y + w3 * A_3D.z;

        // change in z when we increase / decrease x
        double dzdx = w1/(-d*k);

        // change in z when we increase / decrease y
        double dzdy = w2/(-d*k);

        for (int xi = xl; xi <= xr; xi++) {

            // 1/z value
            double z = zg + (xi-xg)*dzdx + (yi-yg)*dzdy;

            if(z < buffer.get(xi,yi)) {
                buffer.set(xi,yi,z);
                (img)(xi, yi) = color;
            }

        }

    }
}

img::EasyImage drawZBufferedLines(Lines2D &lines, int size, vector<double> background_color) {
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
    ZBuffer buffer(lround(image_x), lround(image_y));
    for (auto line : lines){
        draw_zbuf_line(buffer, image, lround(line.p1.x), lround(line.p1.y), line.z1,
                       lround(line.p2.x), lround(line.p2.y), line.z2, line.color);
    }

    return image;
}

img::EasyImage drawZBufferedTriangles(Figures3D& figures, int size, vector<double> background_color) {
    Lines2D lines = doProjection(figures, 1);

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
    double image_x = size * (x_range / max(x_range,y_range));
    double image_y = size * (y_range / max(x_range,y_range));

    // calculate scale factor d
    double d = 0.95 * (image_x / x_range);

    // calculate DC and d of x and y
    double DCx = d * (x_min + x_max)/2;
    double DCy = d * (y_min + y_max)/2;

    double dx = image_x/2 - DCx;
    double dy = image_y/2 - DCy;

    // set background color
    img::Color background = img::Color(lround(background_color[0] * 255),
                                       lround(background_color[1] * 255),
                                       lround(background_color[2] * 255));

    // image constructor
    img::EasyImage image(lround(image_x), lround(image_y), background);

    ZBuffer buffer(lround(image_x), lround(image_y));

    for (auto figure : figures){
        for (auto triangle : figure.faces){
            Vector3D A = Vector3D::point(figure.points[triangle.point_indexes[0]]);
            Vector3D B = Vector3D::point(figure.points[triangle.point_indexes[1]]);
            Vector3D C = Vector3D::point(figure.points[triangle.point_indexes[2]]);


            draw_zbuf_triangle(buffer, image, A, B, C, d, dx, dy, figure.color);
        }
    }

    return image;
}