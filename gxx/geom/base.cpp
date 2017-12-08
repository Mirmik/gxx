#include <gxx/geom/base.h>

namespace gxx { namespace geom {

xyz::xyz(float x, float y, float z) : x(x), y(y), z(z) {}

vector::vector(float x, float y, float z) : xyz(x,y,z) {}

vector::vector(const xyz& oth) : xyz(oth) {}

vector::vector(const vertex& spnt, const vertex& epnt)
    : xyz(epnt.x - spnt.x, epnt.y - spnt.y, epnt.z - spnt.z) {}

direction::direction(float x, float y, float z) : xyz(x,y,z) {}

direction::direction(const xyz& oth) : xyz(oth) {}

vertex::vertex(float x, float y, float z) : xyz(x,y,z) {}

vertex::vertex(const xyz& oth) : xyz(oth) {}

//void xyz::translate(const xyz& vect) {
//    x += vect.x; y += vect.y; z += vect.z;
//}

//xyz xyz::translated(const xyz& vect) {
//    return vertex(x+vect.x, y+vect.y, z+vect.z);
//}
/*
void rotate2d(float& ox, float& oy, float x, float y, float angle) {
    float s = sin(angle);
    float c = cos(angle);

    ox = x*c - y*s;
    oy = x*s + y*c;
}

void xyz::rotateX(float a) {
    float ny, nz; rotate2d(ny,nz,y,z,a); y = ny; z = nz;
}

void xyz::rotateY(float a) {
    float nx, nz; rotate2d(nz,nx,z,x,a); x = nx; z = nz;
}

void xyz::rotateZ(float a) {
    float nx, ny; rotate2d(nx,ny,x,y,a); x = nx; y = ny;
}

xyz xyz::rotatedX(float a) {
    float ny, nz; rotate2d(ny,nz,y,z,a); y = ny; z = nz;
    return xyz(x,ny,nz);
}

xyz xyz::rotatedY(float a) {
    float nx, nz; rotate2d(nz,nx,z,x,a); x = nx; z = nz;
    return xyz(nx,y,nz);
}

xyz xyz::rotatedZ(float a) {
    float nx, ny; rotate2d(nx,ny,x,y,a); x = nx; y = ny;
    return xyz(nx,ny,z);
}*/

//void vertex::translate(const gxx::geom::vector& vect) {
//    xyz::translate(vect);
//}

//vertex vertex::translated(const gxx::geom::vector& vect) {
//    return vertex(xyz::translated(vect));
//}

axis::axis(vertex vrx, direction dir) : vrx(vrx), dir(dir) {}

}}
