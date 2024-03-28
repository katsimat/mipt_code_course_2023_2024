#include <utility>

#include "../circle.h"
#include "../segment.h"
#include "../point.h"
#include "../line.h"


geometry::Circle::Circle(geometry::Point  p, int rad) : center_(std::move(p)), radius_(rad) {}

geometry::IShape& geometry::Circle::Move(const Vector& vec) {
  center_ += vec;
  return *this;
}
bool geometry::Circle::ContainsPoint(const geometry::Point& point) const {
  return radius_ * radius_ >= center_.Distance(point);
}

bool geometry::Circle::CrossesSegment(const geometry::Segment& segment) const {
  Line line = {segment.GetStart(), segment.GetFinish()};
  Point start = segment.GetStart();
  Point finish = segment.GetFinish();
  Vector vec_segment = {start.GetX(), start.GetY(), finish.GetX(), finish.GetY()};
  Vector start_to_center = {start.GetX(), start.GetY(), center_.GetX(), center_.GetY()};
  Vector finish_to_center = {finish.GetX(), finish.GetY(), center_.GetX(), center_.GetY()};
  
  if (vec_segment.Length() == 0) {
    return radius_ * radius_ == center_.Distance(start);
  }
  if (ContainsPoint(start) || ContainsPoint(finish)) {
    return radius_ * radius_ <= center_.Distance(start) ||
            radius_ * radius_ <= center_.Distance(finish);
  }

  if (ScalarProduct(vec_segment, start_to_center) >= 0 && ScalarProduct(-vec_segment, finish_to_center) >= 0) {
    return VectorProduct(start_to_center, vec_segment) * VectorProduct(start_to_center, vec_segment) <= radius_ * radius_ * (vec_segment.Length());
  }

  return std::min(start_to_center.Length(), finish_to_center.Length()) <= radius_ * radius_;
}

geometry::IShape* geometry::Circle::Clone() const {
  return new Circle(center_, radius_);
}

std::string geometry::Circle::ToString() const {
  return "Circle(Point(" + std::to_string(center_.GetX()) + ", " + std::to_string(center_.GetY()) + "), " + std::to_string(radius_) + ")";
}

