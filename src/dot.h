#pragma once

class Dot {
public:
  Dot(unsigned int x, unsigned int y, unsigned int radius) :
    x_(x), y_(y), radius_(radius) {}
  Dot(unsigned int x, unsigned int y, unsigned int radius, int score) :
    x_(x), y_(y), radius_(radius), score_(score) {}

  inline unsigned int x() const { return x_; }
  inline unsigned int y() const { return y_; }
  inline unsigned int radius() const { return radius_; }

  inline int score() const { return score_; }

private:
  // TODO: make const again, currently not due to vector<Dot>.erase()
  //       maybe if we change logic to Exclusive ownership with own move assignment we can circumvent this?
  unsigned int x_;
  unsigned int y_;
  unsigned int radius_;

  int score_{10};
};

