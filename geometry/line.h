#ifndef GEOMETRY_LINE_H
#define GEOMETRY_LINE_H
#include "vector.h"
#include "point.h"
#include "ishape.h"
#include "segment.h"

namespace geometry {
struct Line : public IShape {

  int A = 0;
  int B = 0;
  int C = 0;
  Point start_;
  Point finish_;

  Line() = default;
  Line(int a, int b, int c) : A(a), B(b), C(c) {}
  Line(const Point&, const Point&);
  IShape& Move(const Vector&) final;
  bool ContainsPoint(const Point&) const final;
  bool CrossesSegment(const Segment&) const final;
  IShape* Clone() const final;
  std::string ToString() const final;

    Vector NormalVector() const {
    return {A, B};
  }

  Vector GuideVector() const {
    return {B, -A};
  }

  int64_t DistanceToLineAA(const Point& point);

};

std::istream& operator>>(std::istream& is, Line& line);

bool IsParallel(const Line& first, const Line& second);

}

#endif // GEOMETRY_LINE_H
