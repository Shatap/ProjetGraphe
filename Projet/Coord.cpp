#include "Coord.h"
#include <assert.h>
#include <math.h>

Coord::Coord () : Coord{0.,0.}{}

Coord::Coord(float x, float y) : m_x{x}, m_y{y}
{}

float Coord::norm() const {
    return sqrt((m_x*m_x + m_y*m_y));
}

bool Coord::operator==(const Coord &c) const {
    return c.m_x == m_x && c.m_y == m_y;
}

Coord Coord::operator+(const Coord &c) const {
    return Coord{m_x+c.m_x, m_y+c.m_y};
}


Coord Coord::operator-(const Coord &c)const {
    return Coord{m_x-c.m_x, m_y-c.m_y};
}

Coord& Coord::operator+=(const Coord &c) {
    m_x += c.m_x;
    m_y += c.m_y;
    return *this;
}


Coord& Coord::operator-=(const Coord &c) {
    m_x -= c.m_x;
    m_y -= c.m_y;
    return *this;
}

Coord Coord::operator*(const float &f) const {
    return Coord {m_x * f, m_y * f};
}

Coord Coord::operator/(const float &f) const {
    return Coord {m_x / f, m_y / f};
}


Coord& Coord::operator*=(const float &f) {
    m_x *= f;
    m_y *= f;
    return *this;
}

Coord& Coord::operator/=(const float &f)  {
    assert(fabs(f) > 1E-4);
    m_x /= f;
    m_y /= f;
    return *this;
}
