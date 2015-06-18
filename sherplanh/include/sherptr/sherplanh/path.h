#include <vector>
#include <utility>
#include <sherptr/sherplanh/point.h>

#ifndef __SHERPLANH_PATH__

#define __SHERPLANH_PATH__

class CellGrid;
class Path;

class Path
{
  public:
    Path();
    Path(Path const &orig);

    Point getLast() const;

    bool isEmpty() const;

    bool append(Point const &point);

    unsigned int getCost() const;

    unsigned int getValue(CellGrid const& world, bool wideview) const;

    void truncateToLength(unsigned int newLength);

    void truncateToCost(unsigned int maxCost);

    const std::vector<Point>& getPath() const;

    static bool comparePathsByCostDesc(Path const &A, Path const &B);

    static bool comparePathsByCostAsc(Path const &A, Path const &B);

    static bool comparePathsByValue(CellGrid const &world, bool wideview, Path const &A, Path const &B);
    
  private:
    std::vector<Point> points;
};

#endif
