#include "module.h"

#include <cmath>

using namespace std;

module::module(int id, double area, double aspect_ratio, modType type){
    this->id = id;
    this->area = area;
    this->aspect_ratio = aspect_ratio;
    this->type = type;
    this->width = sqrt(area * aspect_ratio);
    this->height = sqrt(area / aspect_ratio);
}
