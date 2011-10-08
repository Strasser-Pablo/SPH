#include "world.h"
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
World::World(){
  fstream infile("default");
  boost::archive::binary_iarchive ar(infile);
 // boost::archive::xml_iarchive ar(infile);
  bool b;
  ar>>BOOST_SERIALIZATION_NVP(b);

  while(b){
      double t;
   ar>>BOOST_SERIALIZATION_NVP(t);
   Particle_List part(t);
   part.read(ar);
   m_list.push_back(part);
   m_list_t.push_back(t);
    ar>>BOOST_SERIALIZATION_NVP(b);
  }
}

void World::Do()
{
cout<< m_list.size()<<endl;
cout<<m_list.begin()->Size()<<endl;
}
