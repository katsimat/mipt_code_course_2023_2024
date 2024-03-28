#include "../vector.h"

int64_t Vector::Length() const {
  return x * x + y * y;
}

std::string Vector::ToString() const {
  return "Vector(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

Vector Vector::operator+() const {
  return {x, y};
}

Vector& Vector::operator+=(Vector other) {
  *this = *this + other;
  return *this;
}

Vector Vector::operator+(Vector other) const {
  int x_ord = x + other.x;
  int y_ord = y + other.y;
  return {x_ord, y_ord};
}

Vector Vector::operator-() const {
  return {-x, -y};
}

Vector& Vector::operator-=(Vector other) {
  *this = *this - other;
  return *this;
}

Vector Vector::operator-(Vector other) const {
  int x_ord = x - other.x;
  int y_ord = y - other.y;
  return {x_ord, y_ord};
}

Vector& Vector::operator*=(int scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

Vector Vector::operator*(int scalar) const {
  return {x * scalar, y * scalar};
}

Vector Vector::operator/(int scalar) const {
  // Обработка деления на ноль опущена для простоты
  return {x / scalar, y / scalar};
}

bool Vector::operator==(const Vector& other) const {
  return x == other.x && y == other.y;
}

Vector operator*(int scalar, const Vector& vec) {
  return vec * scalar;
}

int64_t ScalarProduct(const Vector& first, const Vector& second) {
  return (first.x * second.x + first.y * second.y);
}

int64_t VectorProduct(const Vector& first, const Vector& second) {
  return (first.x * second.y - first.y * second.x);
}

std::istream& operator>>(std::istream& is, Vector& vec) {
  is >> vec.x >> vec.y;
  return is;
}

std::ostream& operator<<(std::ostream& os, Vector& vec) {
  os << vec.x << ' ' << vec.y;
  return os;
}