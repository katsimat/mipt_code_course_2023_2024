#ifndef GEOMETRY_CIRCLE_H
#define GEOMETRY_CIRCLE_H

#include "vector.h"
#include "ishape.h"
#include "point.h"
namespace geometry {
  struct Circle : public IShape {
   private:
    Point center_;
    int radius_ = 0;
   public:
    Circle(Point , int);
    IShape& Move(const Vector&) final;
    bool ContainsPoint(const Point&) const final;
    bool CrossesSegment(const Segment&) const final;
    IShape* Clone() const final;
    std::string ToString() const final;
  };
}

#endif //GEOMETRY_CIRCLE_H
