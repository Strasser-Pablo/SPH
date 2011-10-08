#ifndef WORLD_TEST_H
#define WORLD_TEST_H

#include "world.h"
#include "particles_list.h"
#include <fstream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

using namespace std;

class World_test:public World{

public:
  World_test();
  void Do();
};


#endif //WORLD_TEST_H