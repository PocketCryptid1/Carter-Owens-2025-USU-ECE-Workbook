#ifndef FLOORPLAN
#define FLOORPLAN

#include "module.h"

#include <string>
#include <vector>
using namespace std;

class floorplan
{
    public:
        vector<module*> modules;

        double cost(string NPE);
        floorplan();
};

#endif