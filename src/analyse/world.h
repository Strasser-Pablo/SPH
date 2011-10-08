#ifndef WORLD_H
#define WORLD_H
#include "particle_list.h"
#include <deque>
using namespace std;
class World{
  deque<Particle_List> m_list;
  deque<double> m_list_t;
public:
  World();
 void Do();
};
#endif //WORLD_H