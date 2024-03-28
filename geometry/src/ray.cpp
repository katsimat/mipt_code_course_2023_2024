#include "../ray.h"
#include "../segment.h"
#include "../point.h"
#include "../vector.h"

geometry::Ray::Ray(const Point& a, const Point& b) : point_(a), vec_(a.GetX(), a.GetY(), b.GetX(), b.GetY()) {
}

geometry::Ray geometry::Ray::operator-() const {
      return {point_, -vec_};
    }

bool geometry::Ray::CrossesSegment(const Segment& seg) const {
  Point seg_a = seg.GetStart();
  Point seg_b = seg.GetFinish();
  Vector pa = {point_.GetX(), point_.GetY(), seg_a.GetX(), seg_a.GetY()};
  Vector pray = vec_;
  Point point_ray = point_;
  Point ray_end = point_ray.Move(vec_);
  Vector pb = {point_.GetX(), point_.GetY(), seg_b.GetX(), seg_b.GetY()};
  Vector ab = {seg_a.GetX(), seg_a.GetY(), seg_b.GetX(), seg_b.GetY()};
  // эти переменные тут появились только чтобы значение влезло в int64_t
  Vector bray_end = {seg_b.GetX(), seg_b.GetY(), ray_end.GetX(), ray_end.GetY()};
  int64_t vp_pray_pb = VectorProduct(pray, pb);
  int64_t vp_ab_bray_end = VectorProduct(ab, bray_end);
  if (vp_pray_pb == 0) {
    vp_pray_pb = 1;
  }
  if (vp_ab_bray_end == 0) {
    vp_ab_bray_end = 1;
  }


  bool intersect = static_cast<bool>(static_cast<long double>(VectorProduct(pray, pa)) / vp_pray_pb < 0 &&
                                     static_cast<long double>(VectorProduct(ab, -pb)) / vp_ab_bray_end < 0);
  intersect = intersect || ContainsPoint(seg_a);
  intersect = intersect || ContainsPoint(seg_b);
  intersect = intersect || seg.ContainsPoint(point_);
  intersect = intersect || seg.ContainsPoint(ray_end);
  return intersect;
}


geometry::Ray *geometry::Ray::Clone() const {
  return new Ray(*this);
}

std::string geometry::Ray::ToString() const {
  return "Ray(" + point_.ToString() + ", " + vec_.ToString() + ")";
}

geometry::IShape &geometry::Ray::Move(const Vector &vector) {
  point_.Move(vector);
  return *this;
}

bool geometry::Ray::ContainsPoint(const geometry::Point &my_point) const {
  Vector first = vec_;
  Vector second = {point_.GetX(), point_.GetY(), my_point.GetX(), my_point.GetY()};
  if (vec_.x * vec_.x + vec_.y * vec_.y == 0) {
    return geometry::Point(point_).ContainsPoint(my_point);
  }
  if (!VectorProduct(first, second)) {
    return ScalarProduct(first, second) >= 0;
  }
  return false;
}

// long double DistanceToRay(const geometry::Point& point, const geometry::Ray& ray) {
//   Vector to_point(ray.GetPoint().GetX(), ray.GetPoint().GetY(), point.GetX(), point.GetY());
//   if (ScalarProduct(ray.GetVector(), to_point) > 0) {
//       return static_cast<long double>(std::abs(VectorProduct(ray.GetVector(), to_point)) / ray.GetVector().Length());
//   }
//   return to_point.Length();
// }