#ifndef POINT_H
#define POINT_H

#include "ishape.h"
#include "vector.h"
#include <iostream>
#include <cmath>
#include <string>

namespace geometry {

struct Point : public IShape {
private:
    int x_ = 0;
    int y_ = 0;

public:
    Point() = default;
    Point(int x, int y) : x_(x), y_(y) {}

    int GetX() const;
    int GetY() const;
    void SetX(int new_x);
    void SetY(int new_y);
    bool ContainsPoint(const Point& other) const override;
    bool CrossesSegment(const Segment& seg) const override;
    Point& Move(const Vector& vector) override;
    std::string ToString() const override;
    IShape* Clone() const override;
    bool operator==(const Point& other) const;
    int64_t Distance(const Point& other) const;
    Point& operator+=(const Vector& other);
    Vector operator-(const Point& other) const;
};

} // namespace geometry

#endif // POINT_H
