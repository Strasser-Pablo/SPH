#include "particles_list.h"
#include "const.h"
void Particles_List::Compute()
{
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.ComputeDensity();
    }
     bool ret=false;
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        ret=it->second.PreComputeMove(DT)||ret;
    }
	if(ret){
	CorrectDensity();	
	}
    m_t+=DT;
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.Update(this);
    }

    #if DOXYGEN
    ParticleReal p;
    p.ComputePressure_Density();
    p.ComputeSurface_Tensor();
    p.ComputeInternal_Force();
    p.ComputeInternal_Force();
    p.ComputeGravity_Force();
    p.ComputeMove(DT);
    p.Update(this);
    #endif //DOXYGEN
}

Particles_List::Particles_List():m_t(0)
{

}

void Particles_List::Dump() {
  cout<<"Begin Particle List"<<endl;
    for (map< Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
      it->first.Dump();
        it->second.Dump();
    }
    cout<<"End Particle List"<<endl;
}

void Particles_List::Prepare()
{
  for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.ComputeDensity();
    }

    #if DOXYGEN
    ParticleReal p;
    p.ComputePressure_Density();
    #endif //DOXYGEN
}

 void Particles_List::InitializeCG(){
  for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.InitializeCG();
    }
}

double Particles_List::CalculateAlpha(double &num){
    double denom;
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.CalculateAlphaPart(num,denom);
    }
return num/denom;
}

double Particles_List::CalculateBeta(double &denom,bool &bret,double alpha){
    double num;
    bool b=true;
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.CalculateBetaPart(num,b,alpha);
    }
    bret=b;
return num/denom;
}

void Particles_List::CalculateP1(double beta){
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.CalculateP1(beta);
    }
}

void Particles_List::ConjugateGradiant(){
InitializeCG();
bool bcont=false;

while(!bcont){
    double num;
double alpha=CalculateAlpha(num);
double beta=CalculateBeta(num,bcont,alpha);
CalculateP1(beta);
}
}

void Particles_List::CorrectDensity(){
bool bcont=true;
while(bcont){
    bcont=false;
ConjugateGradiant();
SetB_Speed();
ConjugateGradiant();
PreparePosition(bcont);
 }
}

void Particles_List::SetB_Speed(){
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.SetB_Speed();
    }
}

void Particles_List::PreparePosition(bool &b){
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.PreparePosition(b);
    }
 }

