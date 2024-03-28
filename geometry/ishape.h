#ifndef GEOMETRY_ISHAPE_H
#define GEOMETRY_ISHAPE_H

#include "vector.h"

namespace geometry {
  struct Segment;
  struct Point;
  struct Ray;

  class IShape {
  public:
    virtual ~IShape() = default;
    virtual IShape& Move(const Vector&) = 0;
    virtual bool ContainsPoint(const Point&) const = 0;
    virtual bool CrossesSegment(const Segment&) const = 0;
    virtual IShape* Clone() const = 0;
    virtual std::string ToString() const = 0;
  };
}


#endif //GEOMETRY_ISHAPE_H
