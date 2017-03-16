#ifndef COORD_H
#define COORD_H

class Coord
{
public:
    float m_x, m_y;

    Coord();
    Coord(float x, float y);

    float norm() const;

    bool operator==(const Coord &c) const ;
    Coord operator+(const Coord &c) const ;
    Coord operator-(const Coord &c) const ;
    Coord& operator+=(const Coord &c);
    Coord& operator-=(const Coord &c);

    Coord operator*(const float &f) const ;
    Coord operator/(const float &f) const;
    Coord& operator*=(const float &f);
    Coord& operator/=(const float &f);
};

#endif // COORD_H
