#ifndef WORLD_H
#define WORLD_H
#include "particle_list.h"
#include <deque>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;
class World{
  deque<Particle_List> m_list;
  deque<double> m_list_t;
  int m_current;
public:
  World();
 void Do();
 void Draw(GLUquadric* param);
 void Next();
};
#endif //WORLD_H