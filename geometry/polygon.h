#ifndef GEOMETRY_POLYGON_H
#define GEOMETRY_POLYGON_H
#include "ishape.h"
#include "vector.h"
#include "point.h"
#include "segment.h"
#include <vector>

namespace geometry {
  struct Polygon : public IShape {
   private:
    std::vector<Point> polygon_;
   public:
    std::vector<Point> GetPolygon() const {
      return polygon_;
    }
    explicit Polygon(const std::vector<Point>& pol) {
      polygon_.reserve(pol.size());
      for (const auto & i : pol) {
        polygon_.emplace_back(i);
      }
    }
    IShape& Move(const Vector&) final;
    bool ContainsPoint(const Point&) const final;
    bool CrossesSegment(const Segment&) const final;
    IShape* Clone() const final;
    std::string ToString() const final;
  };
}


#endif //GEOMETRY_POLYGON_H
