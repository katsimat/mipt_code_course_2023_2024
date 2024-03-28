#include "../polygon.h"
#include "../ray.h"
#include "../point.h"
#include "../vector.h"
#include "../segment.h"


geometry::IShape &geometry::Polygon::Move(const Vector& vec) {
  for (auto & i : polygon_) {
    i += vec;
  }
  return *this;
}

bool geometry::Polygon::ContainsPoint(const geometry::Point& point) const {
  int64_t cnt_intersection = 0;
  geometry::Point big_point = Point(point.GetX() + 1, 2'000'000);
  geometry::Ray ray = Ray(point, big_point);
  for (size_t i = 0; i < polygon_.size(); ++i) {
    geometry::Segment seg = {polygon_[i], polygon_[(i + 1) % polygon_.size()]};
    if (point.CrossesSegment(seg)) {
      return true;
    }
    if (ray.CrossesSegment(seg)) {
      ++cnt_intersection;
    }
  }

  return cnt_intersection % 2;
}

bool geometry::Polygon::CrossesSegment(const geometry::Segment& segment) const {
  bool crossed = false;
  for (size_t i = 0; i < polygon_.size() - 1; ++i) {
    geometry::Segment seg = {polygon_[i], polygon_[(i + 1) % polygon_.size()]};
    crossed = crossed || seg.CrossesSegment(segment);
  }
  return crossed;
}

geometry::IShape *geometry::Polygon::Clone() const {
  return new Polygon(polygon_);
}

std::string geometry::Polygon::ToString() const {
  std::string string = "Polygon(";
  string += polygon_[0].ToString();
  for (size_t i = 1; i < polygon_.size(); ++i) {
    string += ", " + polygon_[i].ToString();
  }
  string += ")";
  return string;
}
