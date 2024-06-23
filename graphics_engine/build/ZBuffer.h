#include <vector>
#include <sstream>
#include "utils/easy_image.h"
#include "Lines2D.h"

using namespace std;
using namespace img;

class ZBuffer: public vector<vector<double>> {
public:
    //Constructor: maakt een Z-Buffer van de correcte grootte aan en initialiseert alle velden op +inf
    ZBuffer(const int width, const int height);

    double get(unsigned int x, unsigned int y);

    void set(unsigned int x, unsigned int y, double value);
};

void draw_zbuf_line(ZBuffer &buffer, EasyImage &image, unsigned int x0, unsigned int y0, double z0, unsigned int x1, unsigned int y1, double z1, const Color &color);

void draw_zbuf_triangle(ZBuffer &buffer, img::EasyImage &image,
                        Vector3D const& A, Vector3D const& B, Vector3D const& C,
                        double d, double dx, double dy, const Color& color);

img::EasyImage drawZBufferedLines(Lines2D &lines, int size, vector<double> background_color);

img::EasyImage drawZBufferedTriangles(Figures3D& figures, int size, vector<double> background_color);