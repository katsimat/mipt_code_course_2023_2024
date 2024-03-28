#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

struct Vector {
  int x = 0;
  int y = 0;

  Vector() = default;
  Vector(int x_ord, int y_ord) : x(x_ord), y(y_ord) {}
  Vector(int start_x, int start_y, int end_x, int end_y) : x(end_x - start_x), y(end_y - start_y) {}
  Vector(const Vector& other) = default;

  int64_t Length() const;
  std::string ToString() const;

  Vector operator+() const;
  Vector& operator+=(Vector other);
  Vector operator+(Vector other) const;
  Vector operator-() const;
  Vector& operator-=(Vector other);
  Vector operator-(Vector other) const;
  Vector& operator*=(int scalar);
  Vector operator*(int scalar) const;
  Vector operator/(int scalar) const;
  Vector& operator=(const Vector& other) = default;
  bool operator==(const Vector& other) const;
};

Vector operator*(int scalar, const Vector& vec);

int64_t ScalarProduct(const Vector& first, const Vector& second);
int64_t VectorProduct(const Vector& first, const Vector& second);



std::istream& operator>>(std::istream& is, Vector& vec);
std::ostream& operator<<(std::ostream& os, Vector& vec);

#endif // VECTOR_H
