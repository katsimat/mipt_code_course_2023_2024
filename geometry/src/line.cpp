#include "../line.h"
#include "../vector.h"

geometry::IShape& geometry::Line::Move(const Vector& vec) {
  C -= A * vec.x + B * vec.y;
  return *this;
}

bool geometry::Line::ContainsPoint(const Point& point) const {
  return A * point.GetX() + B * point.GetY() + C == 0;
}

bool geometry::Line::CrossesSegment(const Segment& segment) const {
  // points coordinates
  int x1 = segment.GetStart().GetX();
  int y1 = segment.GetStart().GetY();
  int x2 = segment.GetFinish().GetX();
  int y2 = segment.GetFinish().GetY();

  // line with point above the this_line
  int c1 = A * x1 + B * y1 + C;

  // line with point under the this_line
  int c2 = A * x2 + B * y2 + C;

  return c1 * c2 <= 0;
}

geometry::IShape* geometry::Line::Clone() const {
  return new Line(*this);
}

std::string geometry::Line::ToString() const {
  return "Line(" + std::to_string(A) + ", " + std::to_string(B) + ", " + std::to_string(C) + ")";
}

geometry::Line::Line(const geometry::Point &point1, const geometry::Point &point2) {
  A = point2.GetY() - point1.GetY();
  B = point1.GetX() - point2.GetX();
  C = point1.GetY() * (point2.GetX() - point1.GetX()) - point1.GetX() * (point2.GetY() - point1.GetY());
  start_ = point1;
  finish_ = point2;
}


std::istream& operator>>(std::istream& is, geometry::Line& line) {
  is >> line.A >> line.B >> line.C;
  return is;
}

bool geometry::IsParallel(const geometry::Line& first, const geometry::Line& second) {
  return VectorProduct(first.GuideVector(), second.GuideVector()) == 0;
}

int64_t geometry::Line::DistanceToLineAA(const geometry::Point& point) {
  Vector to_point = {point.GetX(), point.GetY()};
  Vector to_line = {start_.GetX(), start_.GetY()};
  Vector line_vec = {start_.GetX(), start_.GetX(), finish_.GetX(), finish_.GetY()};
  int64_t distance = VectorProduct(to_point - to_line, line_vec);
  return distance;
}

