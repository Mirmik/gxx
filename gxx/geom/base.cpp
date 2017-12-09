#include <gxx/geom/base.h>

/*namespace gxx { namespace geom {

XYZ::XYZ(float x, float y, float z) : x(x), y(y), z(z) {}

Vector::Vector(float x, float y, float z) : XYZ(x,y,z) {}

Vector::Vector(const XYZ& oth) : XYZ(oth) {}

Vector::Vector(const Point& spnt, const Point& epnt)
    : XYZ(epnt.x - spnt.x, epnt.y - spnt.y, epnt.z - spnt.z) {}

Direction::Direction(float x, float y, float z) {
    float mod = sqrt(x*x + y*y + z*z);
    this->x = x / mod;
    this->y = y / mod;
    this->z = z / mod; 
}

Direction::Direction(const XYZ& oth) : Direction(oth.x, oth.y, oth.z) {}

Point::Point(float x, float y, float z) : XYZ(x,y,z) {}

Point::Point(const XYZ& oth) : XYZ(oth) {}
*/
//void XYZ::translate(const XYZ& vect) {
//    x += vect.x; y += vect.y; z += vect.z;
//}

//XYZ XYZ::translated(const XYZ& vect) {
//    return Point(x+vect.x, y+vect.y, z+vect.z);
//}
/*
void rotate2d(float& ox, float& oy, float x, float y, float angle) {
    float s = sin(angle);
    float c = cos(angle);

    ox = x*c - y*s;
    oy = x*s + y*c;
}

void XYZ::rotateX(float a) {
    float ny, nz; rotate2d(ny,nz,y,z,a); y = ny; z = nz;
}

void XYZ::rotateY(float a) {
    float nx, nz; rotate2d(nz,nx,z,x,a); x = nx; z = nz;
}

void XYZ::rotateZ(float a) {
    float nx, ny; rotate2d(nx,ny,x,y,a); x = nx; y = ny;
}

XYZ XYZ::rotatedX(float a) {
    float ny, nz; rotate2d(ny,nz,y,z,a); y = ny; z = nz;
    return XYZ(x,ny,nz);
}

XYZ XYZ::rotatedY(float a) {
    float nx, nz; rotate2d(nz,nx,z,x,a); x = nx; z = nz;
    return XYZ(nx,y,nz);
}

XYZ XYZ::rotatedZ(float a) {
    float nx, ny; rotate2d(nx,ny,x,y,a); x = nx; y = ny;
    return XYZ(nx,ny,z);
}*/

//void Point::translate(const gxx::geom::Vector& vect) {
//    XYZ::translate(vect);
//}

//Point Point::translated(const gxx::geom::Vector& vect) {
//    return Point(XYZ::translated(vect));
//}

//Axis::Axis(const Point& pnt, const Direction& dir) : pnt(pnt), dir(dir) {}

//}}
