#include "particles_list.h"
#include "const.h"
void Particles_List::Compute()
{
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.ComputePressure_Density();
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
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.Update(m_list);
    }
}
