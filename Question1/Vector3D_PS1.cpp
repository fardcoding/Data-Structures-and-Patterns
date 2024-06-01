#include "Vector3D.h"

#include <math.h>
#include <sstream>

float roundNum(float aNum) {
    double customPrecision = 1e4;
    return round(aNum * customPrecision) / customPrecision;
}
std::string Vector3D::toString() const noexcept {
    std::stringstream customResult;
    customResult << "[" << roundNum(x()) << "," << roundNum(y()) << "," << roundNum(w()) << "]";
    return customResult.str();
}













