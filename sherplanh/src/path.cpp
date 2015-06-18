#include <sherptr/sherplanh/cellgrid.h>
#include <sherptr/sherplanh/path.h>

Path::Path(){};

Path::Path(Path const &orig):
  points(orig.points)
{};

Point Path::getLast() const
{
  Point retq;
  retq.first = 0;
  retq.second = 0;
  if(points.size())
    retq = points[points.size()-1];
  return retq;
}

bool Path::isEmpty() const
{
  return (0 == points.size());
}

bool Path::append(Point const &point)
{
  bool retq = false;
  Point last = getLast();
  if(!points.size())
  {
    retq = true;
    points.push_back(point);
  }
  else
  {
    if(last.isAdjacentTo(point))
    {
      retq = true;
      points.push_back(point);
    }
  }
  return retq;
}

unsigned int Path::getCost() const
{
  if(!points.size())
    return 0;
  return(points.size() - 1);
}

unsigned int Path::getValue(CellGrid const& world, bool wideview) const
{
  unsigned int retq = 0;
  if(wideview)
  {
    CellGrid aux(world.getRows(), world.getCols());
    for(int k = 0; k < points.size(); k++)
    {
      aux.setValue(points[k], 1);
      std::vector<Point> adj = world.getAdjacents(points[k]);
      for(int j = 0; j < adj.size(); j++)
        aux.setValue(adj[j], 1);
    }
    for(int k = 0; k < world.getRows(); k++)
      for(int j = 0; j < world.getCols(); j++)
        retq += (aux.getValue(k, j))?(world.getValue(k, j)):(0);
  }
  else
  {
    for(int k = 0; k < points.size(); k++)
      retq += world.getValue(points[k]);
  }
  return retq;
}

void Path::truncateToLength(unsigned int newLength)
{
  if(newLength < points.size())
    points.resize(newLength);
}

void Path::truncateToCost(unsigned int maxCost)
{
  truncateToLength(maxCost + 1);
}

const std::vector<Point>& Path::getPath() const
{
  return points;
}

bool Path::comparePathsByCostDesc(Path const &A, Path const &B)
{
  unsigned int cA, cB;
  cA = A.getCost();
  cB = B.getCost();
  /*Heap: return true if A is lesser and B should be closer to the top. Will want the highest element to have the lowest cost.*/
  /*Sort: return true whether A comes before B under the order relation.*/
  return (cA > cB); 
}

bool Path::comparePathsByCostAsc(Path const &A, Path const &B)
{
  unsigned int cA, cB;
  cA = A.getCost();
  cB = B.getCost();
  /*Sort: return true whether A comes before B under the order relation.*/
  return (cA < cB); 
}

bool Path::comparePathsByValue(CellGrid const &world, bool wideview, Path const &A, Path const &B)
{
  unsigned int cA, cB;
  cA = A.getValue(world, wideview);
  cB = B.getValue(world, wideview);
  return (cA < cB); /*Will want the highest element to have the highest value.*/
}

