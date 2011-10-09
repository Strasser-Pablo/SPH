#ifndef WORLD_H
#define WORLD_H
#include "particle_list.h"
#include <deque>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
using namespace std;
class World{
 Particle_List m_list;
  double m_list_t;
  int m_current;
  fstream m_infile;
  bool m_finish;
   boost::archive::binary_iarchive m_ar;
public:
  World();
 void Do();
 void Draw(GLUquadric* param);
 void Next();
};
#endif //WORLD_H