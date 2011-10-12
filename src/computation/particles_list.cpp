#include "particles_list.h"
#include "const.h"
void Particles_List::Compute()
{
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.ComputePressure_Density();
    }
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second. ComputeSurface_Tensor();
    }
   
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.ComputeInternal_Force();
    }
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.ComputeGravity_Force();
    }
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.ComputeMove(DT);
        
    }
    m_t+=DT;
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.Update(this);
    }
}

Particles_List::Particles_List():m_t(0)
{

}

void Particles_List::Dump() {
  cout<<"Begin Particle List"<<endl;
    for (map< Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
      it->first.Dump();
        it->second.Dump();
    }
    cout<<"End Particle List"<<endl;
}

void Particles_List::Prepare()
{
  for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.ComputePressure_Density();
    }
}


