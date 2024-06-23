#define _USE_MATH_DEFINES
#include "Figure3D.h"
#include "cmath"

using namespace std;

Figure::Figure() = default;

void Figure::applyTransformation(const Matrix &m) {
    for(auto &point : this->points){
        point *= m;
    }
}

void applyTransformationAll(Figures3D &figs, const Matrix &m){
    for(auto& figure : figs){

        // for each point in figure apply transformation
        for(auto &point : figure.points){
            point *= m;
        }
    }
}

