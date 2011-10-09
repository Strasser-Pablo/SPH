#include "world.h"

World::World():m_current(0),m_infile("default"),m_ar(m_infile),m_finish(false){

    bool b;
  m_ar>>BOOST_SERIALIZATION_NVP(b);
cout<<"b "<<b<<endl;
  if(b){
      double t;
   m_ar>>BOOST_SERIALIZATION_NVP(t);
   Particle_List part;
   part.read(m_ar);
   m_list=part;
   m_list_t=t;
cout<<"ready"<<endl;

  }else{
m_finish=true;
  }
}

void World::Do()
{

}

void World::Draw(GLUquadric* param)
{
  
     cout<<"t "<<m_list_t<<endl;
   m_list.Draw(param);
   cout<<"finish"<<endl;
}

void World::Next()
{
  if(!m_finish){
 bool b;
  m_ar>>BOOST_SERIALIZATION_NVP(b);
cout<<"b "<<b<<endl;
  if(b){
      double t;
   m_ar>>BOOST_SERIALIZATION_NVP(t);
   Particle_List part;
   part.read(m_ar);
   m_list=part;
   m_list_t=t;
cout<<"ready"<<endl;

  }
  else{
   m_finish=true; 
  }
  }else{
   cout<<"finished no possible to take next frame"<<endl; 
  }
}
