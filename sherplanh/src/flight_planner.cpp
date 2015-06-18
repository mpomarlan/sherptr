#include <sherptr/sherplanh/flight_planner.h>

void kShortestPaths(CellGrid const &world, Point const &start, Point const &dest, unsigned int K, std::vector<Path> &paths)
{
  unsigned int addedPaths = 0;
  CellGrid pathCounts(world.getRows(), world.getCols());
  std::vector<Path> B;
  Path Ps; Ps.append(start);
  B.push_back(Ps);
  std::make_heap(B.begin(), B.end(), Path::comparePathsByCostDesc);
  while(B.size() && (addedPaths < K))
  {
    Path Pu(B.front());
    Point u = Pu.getLast();
    std::pop_heap(B.begin(), B.end(), Path::comparePathsByCostDesc);B.pop_back();
    pathCounts.setValue(u, pathCounts.getValue(u) + 1);
    if((u.first == dest.first) && (u.second == dest.second))
    {
      paths.push_back(Pu);
      addedPaths++;
    }
    if(pathCounts.getValue(u) <= K)
    {
      std::vector<Point> vs = world.getAdjacents(u);
      for(int k = 0; k < vs.size(); k++)
      {
        Path Pv(Pu);
        Pv.append(vs[k]);
        B.push_back(Pv); std::push_heap(B.begin(), B.end(), Path::comparePathsByCostDesc);
      }
    }
  }
}

void truncatePaths(std::vector<Path> &paths, unsigned int maxCost, bool rejectUnfeasible)
{
  std::sort(paths.begin(), paths.end(), Path::comparePathsByCostAsc);
  int mx = paths.size();
  for(int k = 0; (k < paths.size()) && (k < mx); k++)
    if(maxCost < paths[k].getCost())
      mx = k;
  if(rejectUnfeasible)
    paths.resize(mx);
  else
    for(int k = mx; k < paths.size(); k++)
      paths[k].truncateToLength(maxCost + 1);
}

Path selectBestPath(std::vector<Path> const &paths, CellGrid const &world, bool wideview)
{
  if(!paths.size())
    return Path();
  int b = 0;
  for(int k = 1; k < paths.size(); k++)
    if(paths[b].getValue(world, wideview) < paths[k].getValue(world, wideview))
      b = k;
  return paths[b];
}

Path planBotFlight(CellGrid &world, std::vector<Point> const &returnPoints, Bot const &botp)
{
  Bot bot(botp);

  std::vector<Path> paths; paths.clear();

  bot.distancesToReturns.clear();
  for(int k = 0; k < returnPoints.size(); k++)
    bot.distancesToReturns.push_back(Point(Point::ChebyshevDistance(bot.start, returnPoints[k]), k));

  std::sort(bot.distancesToReturns.begin(), bot.distancesToReturns.end(), Bot::compareReturns);

  for(int k = 0; k < bot.distancesToReturns.size(); k++)
    kShortestPaths(world, bot.start, returnPoints[bot.distancesToReturns[k].second], KPATHS, paths);

  truncatePaths(paths, bot.charge, bot.boomerang);
  Path retq(selectBestPath(paths, world, bot.wideview));
  if(retq.isEmpty())
    retq.append(bot.start);
  world.clearValuesOnPath(retq, bot.wideview);
  return retq;
}

void flightPlanner(std::vector<Bot> const &botsp, CellGrid const &worldp, std::vector<Point> const &returnPoints, std::vector<std::pair<unsigned int, Path> > &plannedPaths)
{
  plannedPaths.clear();
  
  std::vector<Bot> boomerangs; boomerangs.clear();
  std::vector<Bot> pioneers; pioneers.clear();
  for(int k = 0; k < botsp.size(); k++)
    if(botsp[k].boomerang)
      boomerangs.push_back(botsp[k]);
    else
      pioneers.push_back(botsp[k]);

  for(int k = 0; k < boomerangs.size(); k++)
    boomerangs[k].adjustEffectiveCharge();
  for(int k = 0; k < pioneers.size(); k++)
    pioneers[k].adjustEffectiveCharge();

  std::sort(boomerangs.begin(), boomerangs.end(), Bot::compareBotsByChargeAsc);
  std::sort(pioneers.begin(), pioneers.end(), Bot::compareBotsByChargeAsc);

  CellGrid world(worldp);

  for(int k = 0; k < boomerangs.size(); k++)
    plannedPaths.push_back(std::pair<unsigned int, Path>(boomerangs[k].id, planBotFlight(world, returnPoints, boomerangs[k])));
}

