#include <algorithm>
#include <vector>
#include <utility>

#include <sherptr/sherplanh/point.h>
#include <sherptr/sherplanh/bot.h>
#include <sherptr/sherplanh/path.h>
#include <sherptr/sherplanh/cellgrid.h>

#ifndef __SHERPLANH_FLIGHT_PLANNER__

#define __SHERPLANH_FLIGHT_PLANNER__

#define KPATHS 30

void kShortestPaths(CellGrid const &world, Point const &start, Point const &dest, unsigned int K, std::vector<Path> &paths);

void truncatePaths(std::vector<Path> &paths, unsigned int maxCost, bool rejectUnfeasible);

Path selectBestPath(std::vector<Path> const &paths, CellGrid const &world, bool wideview);

Path planBotFlight(CellGrid &world, std::vector<Point> const &returnPoints, Bot const &botp);

void flightPlanner(std::vector<Bot> const &botsp, CellGrid const &worldp, std::vector<Point> const &returnPoints, std::vector<std::pair<unsigned int, Path> > &plannedPaths);

#endif

