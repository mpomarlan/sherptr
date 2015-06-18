#include <vector>
#include <utility>
#include <sherptr/sherplanh/point.h>

#ifndef __SHERPLANH_CELLGRID__

#define __SHERPLANH_CELLGRID__

class CellGrid;
class Path;

class CellGrid
{
  public:
    CellGrid(unsigned int rows, unsigned int cols);
    
    CellGrid(CellGrid const &orig);

    unsigned int getRows() const;
    unsigned int getCols() const;

    std::vector<Point> getAdjacents(Point const &A) const;

    unsigned int getValue(unsigned int row, unsigned int col) const;

    unsigned int getValue(Point const &point) const;

    bool setValue(unsigned int row, unsigned int col, unsigned int value);

    bool setValue(Point const &point, unsigned int value);

    bool clearValuesOnPath(Path const &path, bool wideview);

  private:

    bool isInMap(Point const &A, signed int yOff, signed int xOff) const;

    unsigned int rows, cols;
    std::vector<std::vector<unsigned char> > cellValues;
};

#endif

