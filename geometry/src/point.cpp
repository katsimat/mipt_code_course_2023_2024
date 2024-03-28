#include "../point.h"
#include "../segment.h"
#include "../vector.h"
#include "../ray.h"


int geometry::Point::GetX() const {
    return x_;
}

int geometry::Point::GetY() const {
    return y_;
}

void geometry::Point::SetX(int new_x) {
    x_ = new_x;
}

void geometry::Point::SetY(int new_y) {
    y_ = new_y;
}

bool geometry::Point::ContainsPoint(const Point& other) const {
    return *this == other;
}

bool geometry::Point::CrossesSegment(const Segment& segment) const {
    Point start = segment.GetStart();
    Point finish = segment.GetFinish();
    Vector sf = {start.GetX(), start.GetY(), finish.GetX(), finish.GetY()};
    return geometry::Ray(start, sf).ContainsPoint(*this) &&
           geometry::Ray(finish, -sf).ContainsPoint(*this);
}

geometry::Point& geometry::Point::Move(const Vector& vector) {
    x_ += vector.x;
    y_ += vector.y;
    return *this;
}

std::string geometry::Point::ToString() const {
    return "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}

geometry::IShape* geometry::Point::Clone() const {
    return new Point(*this);
}

std::istream& operator>>(std::istream& is, geometry::Point& point) {
    int x = 0;
    int y = 0;
    is >> x >> y;
    point.SetX(x);
    point.SetY(y);
    return is;
}

  bool geometry::Point::operator==(const geometry::Point &other) const {
    return x_ == other.GetX() && y_ == other.GetY();
  }

  int64_t geometry::Point::Distance(const geometry::Point &other) const {
    return (other.GetX() - x_) * (other.GetX() - x_) + (other.GetY() - y_) * (other.GetY() - y_);
  }

  geometry::Point &geometry::Point::operator+=(const Vector &other) {
    x_ += other.x;
    y_ += other.y;
    return *this;
  }

  Vector geometry::Point::operator-(const geometry::Point &other) const {
    return {x_ - other.GetX(), y_ - other.GetY()};
  }
// namespace geometry
