#ifndef SEGMENT
#define SEGMENT

#include "ishape.h"
#include "vector.h"
#include "point.h"
#include <iostream>
#include <utility>

namespace geometry {
  struct Segment : public IShape {
   private:
    static bool RayIntersectSegment(const Ray& ray, const Segment& seg);

    static bool IntersectionOfProjections(int64_t x_first_st, int64_t x_first_fn, int64_t x_second_st, int64_t x_second_fn);

    static int64_t DistanceToRay(const Ray& ray, const geometry::Point& point);

    Point start_;
    Point finish_;

  public:
    Point GetStart() const;

    Point GetFinish() const;

    Segment() = default;
    Segment(const Point&, const Point&);

    Segment(const Segment& other) = default;

    IShape& Move(const Vector& vec) final;
    bool ContainsPoint(const Point& point) const final;
    bool CrossesSegment(const Segment& seg2) const final;
    IShape* Clone() const final;
    std::string ToString() const final;

    int64_t DistanceToSegment(const geometry::Point& point) const;
  };
}

#endif