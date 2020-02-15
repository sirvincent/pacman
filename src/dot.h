#pragma once

class Dot {
public:
  Dot(unsigned int x, unsigned int y, unsigned int radius) :
    x_(x), y_(y), radius_(radius) {}

  inline unsigned int x() const { return x_; }
  inline unsigned int y() const { return y_; }
  inline unsigned int radius() const { return radius_; }

private:
  unsigned int const x_;
  unsigned int const y_;
  unsigned int const radius_;
};

