#ifndef RAY
#define RAY

// #include "point.h"
//#include "segment.h"
#include "ishape.h"
#include "vector.h"
#include "point.h"


#include <string>


namespace geometry {
  struct Ray : public IShape {
   private:
    Point point_;
    Vector vec_;
   public:
    Point GetPoint() const {
      return point_;
    }

    Vector GetVector() const {
      return vec_;
    }

    void SetPoint(const Point& new_point) {
      point_ = new_point;
    }

    void SetVector(const Vector& new_vec_tor) {
      vec_ = new_vec_tor;
    }
    // ~Ray() override = default;
    IShape& Move(const Vector&) final;
    bool ContainsPoint(const Point&) const final;
    bool CrossesSegment(const Segment&) const final;
    Ray* Clone() const final;
    std::string ToString() const final;

    Ray() = default;

    Ray(const Point& p, const Vector& v) : point_(p), vec_(v) {
    }

    Ray(const Point&, const Point&);

    Ray operator-() const;

    bool RayIntersectSegment(const Segment&);
  };
}

long double DistanceToRay(const geometry::Point& point, const geometry::Ray& ray);

#endif // RAY