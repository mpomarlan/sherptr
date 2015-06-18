#include <sherptr/sherplanh/cellgrid.h>
#include <sherptr/sherplanh/path.h>

CellGrid::CellGrid(unsigned int rows, unsigned int cols): 
  rows(rows), cols(cols)
{
  cellValues.resize(rows);
  for(unsigned int k = 0; k < rows; k++)
    cellValues[k].resize(cols, 0);
};
    
CellGrid::CellGrid(CellGrid const &orig):
  rows(orig.rows), cols(orig.cols), cellValues(orig.cellValues)
{
};

unsigned int CellGrid::getRows() const
{
  return rows;
}
unsigned int CellGrid::getCols() const
{
  return cols;
}

std::vector<Point> CellGrid::getAdjacents(Point const &A) const
{
  std::vector<Point> retq;
  retq.clear();
  if(isInMap(A, -1, -1))
    retq.push_back(Point(A, -1, -1));
  if(isInMap(A, -1, 0))
    retq.push_back(Point(A, -1, 0));
  if(isInMap(A, -1, +1))
    retq.push_back(Point(A, -1, +1));

  if(isInMap(A, 0, -1))
    retq.push_back(Point(A, 0, -1));
  if(isInMap(A, 0, +1))
    retq.push_back(Point(A, 0, +1));

  if(isInMap(A, +1, -1))
    retq.push_back(Point(A, +1, -1));
  if(isInMap(A, +1, 0))
    retq.push_back(Point(A, +1, 0));
  if(isInMap(A, +1, +1))
    retq.push_back(Point(A, +1, +1));

  return retq;
}

unsigned int CellGrid::getValue(unsigned int row, unsigned int col) const
{
  unsigned int retq = 0;
  if((row < rows) && (col < cols))
    retq = cellValues[row][col];
  return retq;
}

unsigned int CellGrid::getValue(Point const &point) const
{
  getValue(point.first, point.second);
}

bool CellGrid::setValue(unsigned int row, unsigned int col, unsigned int value)
{
  bool retq = false;
  if((row < rows) && (col < cols))
  {
    cellValues[row][col] = value;
    retq = true;
  }
  return retq;
}

bool CellGrid::setValue(Point const &point, unsigned int value)
{
  return setValue(point.first, point.second, value);
}

bool CellGrid::clearValuesOnPath(Path const &path, bool wideview)
{
  std::vector<Point> points = path.getPath();
  bool retq = true;
  if(wideview)
  {
    CellGrid aux(rows, cols);
    for(int k = 0; k < points.size(); k++)
    {
      retq &= aux.setValue(points[k], 1);
      std::vector<Point> adj = getAdjacents(points[k]);
      for(int j = 0; j < adj.size(); j++)
        aux.setValue(adj[j], 1);
    }
    for(int k = 0; k < rows; k++)
      for(int j = 0; j < cols; j++)
        if(aux.getValue(k, j))
          setValue(k, j, 0);
  }
  else
  {
    for(int k = 0; k < points.size(); k++)
      retq &= setValue(points[k], 0);
  }
  return retq;
}

bool CellGrid::isInMap(Point const &A, signed int yOff, signed int xOff) const
{
  unsigned int px, py;
  px = A.second + xOff;
  py = A.first + yOff;
  return ((py < rows) && (px < cols)); /*A bit of trickery, as negative numbers wrap back into the billions, we only expect +/-1 offsets, and maps won't have billions of rows/cols.*/
}

