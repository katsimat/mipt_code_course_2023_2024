#include "../segment.h"
#include "../point.h"
#include "../ray.h"
#include "../vector.h"

int64_t geometry::Segment::DistanceToRay(const geometry::Ray& ray, const geometry::Point& point) {
  Vector to_point(ray.GetPoint().GetX(), ray.GetPoint().GetY(), point.GetX(), point.GetY());
  if (ScalarProduct(ray.GetVector(), to_point) > 0) {
   return std::abs(VectorProduct(ray.GetVector(), to_point));
  }
  return to_point.Length();
}

std::string geometry::Segment::ToString() const {
  return "Segment(" + start_.ToString() + ", " + finish_.ToString() + ")";
}

geometry::IShape *geometry::Segment::Clone() const {
  auto segment = new Segment(*this);
  return segment;
}

bool geometry::Segment::CrossesSegment(const geometry::Segment &seg2) const {
  Segment seg1 = *this;
  
  if (seg1.GetStart() == seg1.GetFinish()) {
    return seg2.ContainsPoint(seg1.GetStart());
  }

  Vector guide = {seg1.start_.GetX(), seg1.start_.GetY(), seg1.finish_.GetX(), seg1.finish_.GetY()};
  geometry::Ray ray_start_guide = {seg1.GetStart(), guide};
  geometry::Ray ray_finish_guide = {seg1.GetFinish(), -guide};
  
  return (ray_start_guide.CrossesSegment(seg2) &&
          ray_finish_guide.CrossesSegment(seg2));
}

bool geometry::Segment::ContainsPoint(const geometry::Point &point) const {
  return point.CrossesSegment(*this);
}

geometry::IShape &geometry::Segment::Move(const Vector &vec) {
  start_.Move(vec);
  finish_.Move(vec);
  return *this;
}

geometry::Point geometry::Segment::GetStart() const {
  return start_;
}

geometry::Point geometry::Segment::GetFinish() const {
  return finish_;
}

int64_t geometry::Segment::DistanceToSegment(const geometry::Point &point) const {
  Vector vec(start_.GetX(), start_.GetY(), finish_.GetX(), finish_.GetY());
  return std::max(DistanceToRay(Ray(start_, vec), point), DistanceToRay(Ray(finish_, -vec), point));
}

geometry::Segment::Segment(const geometry::Point &a, const geometry::Point &b) : start_(a), finish_(b) {
}
