#include "particle_list.h"

Particle_List::Particle_List(double t):m_t(t)
{

}

void Particle_List::Draw(GLUquadric* param)
{
for(deque<ParticleReal>::iterator it=m_list.begin();it!=m_list.end();it++){
 it->Draw(param); 
}
}
