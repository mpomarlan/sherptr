#include <vector>
#include <sherptr/sherplanh/point.h>

#ifndef __SHERPLANH_BOT__

#define __SHERPLANH_BOT__

class Bot;

class Bot
{
  public:
    Bot():
      start(0, 0), charge(0), id(0), boomerang(false), wideview(false),unitTravelCost(1),distancesToReturns()
    {};
    Bot(Bot const &orig):
      start(orig.start), charge(orig.charge), id(orig.id), boomerang(orig.boomerang), wideview(orig.wideview),unitTravelCost(orig.unitTravelCost),distancesToReturns(orig.distancesToReturns)
    {};

    Point start;
    unsigned int charge;
    unsigned int id;
    bool boomerang;
    bool wideview;
    unsigned int unitTravelCost;
    std::vector<Point> distancesToReturns;

    void adjustEffectiveCharge()
    {
      charge /= unitTravelCost;
    }
    
    static bool compareReturns(Point const &A, Point const &B)
    {
      return(A.first < B.first);
    }

    static bool compareBotsByChargeAsc(Bot const &A, Bot const &B)
    {
      return (A.charge < B.charge);
    }
  private:
};

#endif
