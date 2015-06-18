#ifndef __SHERPLANH_POINT__

#define __SHERPLANH_POINT__

class Point
{
  public:
    Point():
      first(0), second(0)
    {};

    Point(Point const &orig):
      first(orig.first), second(orig.second)
    {};

    Point(unsigned int y, unsigned int x):
      first(y), second(x)
    {};

    Point(Point const &A, signed int y, signed int x):
      first(A.first+y), second(A.second+x)
    {};

    bool isAdjacentTo(Point const &B) const
    {
      return (ChebyshevDistance(*this, B) <= 1);
    }

    unsigned int first, second;

    static unsigned int ChebyshevDistance(Point const &A, Point const &B)
    {
      unsigned int dy = (A.first < B.first)?(B.first - A.first):(A.first - B.first);
      unsigned int dx = (A.second < B.second)?(B.second - A.second):(A.second - B.second);
      return (dx < dy)?(dy):(dx);
    }
};

#endif


