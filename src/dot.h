#pragma once

class Dot {
public:
  Dot(unsigned int x, unsigned int y, unsigned int radius) :
    x_(x), y_(y), radius_(radius) {}

  inline unsigned int x() const { return x_; }
  inline unsigned int y() const { return y_; }
  inline unsigned int radius() const { return radius_; }

private:
  // TODO: make const again, currently not due to vector<Dot>.erase()
  //       maybe if we change logic to Exclusive ownership with own move assignment we can circumvent this?
  unsigned int x_;
  unsigned int y_;
  unsigned int radius_;
};

