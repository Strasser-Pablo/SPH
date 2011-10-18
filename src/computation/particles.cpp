/*
Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
*/
/** \file particles.cpp
 * @brief Implementation file for particles.
 *
 */


#include "particles.h"
#include "particle.h"
#include "particles_list.h"
#include "debug.h"
using namespace std;

 inline double CalculateA(const Particle& A,const Particle& B,Particles & voisin);
   inline double CalculateABas(const Particle& A,const Particle& B);
Particles::Particles(ParticleType type): list<Particle>(),m_type(type)
{

}

Particles::Particles(const Particles& A):m_type(A.m_type),list<Particle>(A) {

}

Particles::Particles():m_type(none)
{

}


void Particles::ComputeDensity()
{

    for (list<Particle>::iterator it=begin();it!=end();++it) {

            (*it)->ComputeDensity();
    }

}





void Particles::SetNeighbour(list< Particles *> list )
{
    m_neighbour=list;
}

list<Particles*> Particles::GetNeighbour(){
  return m_neighbour;
}


bool Particles::PreComputeMove(double dt)
{
    bool ret=false;
    for (list<Particle>::iterator it=begin();it!=end();++it) {
        ret=(*it)->PreComputeMove( dt)|| ret;
    }
    return ret;
}

void Particles::Update( Particles_List*  plist)
{
  list<Particle>::iterator it=begin();
    while (it!=end()) {
      //iterator effectly used
      list<Particle>::iterator it2=it;
      //we increase the iterator before that we splice to don't have problem when it2 is invalided
      it++;
      plist->Update(it2,this);
	}

}

bool Particles::operator==(const Particles& parts) const
{
return this==&parts;
}


void Particles::Dump(bool voisin)
{
  cout<<"begin Particles"<<endl;
for(Particles::iterator it=begin();it!=end();++it){
 (*it)->Dump();
}
if(voisin){
cout<<"dump of neighbour"<<endl;
DumpNeighbour(m_neighbour);
cout<<"end dump of neighbour"<<endl;
}
cout<<"end Particles"<<endl;
}

void Particles::Add(Particle part){
part->SetContainerParticles(this);
push_back(part);

}

void Particles::InitializeCG(){
for(Particles::iterator it=begin();it!=end();++it){
    double b=(*it)->GetB();
    (*it)->SetP(0);
(*it)->SetRprec(b);
(*it)->SetZprec(b);
(*it)->SetP1(b);
}
}

  void Particles::CalculateAlphaPart(double &num,double &denom){
for(Particles::iterator it=begin();it!=end();++it){
 num+=(*it)->MultRZprec();
 Particles voisin;
 (*it)->GetVoisin(voisin);
 double p=(*it)->GetP1();
 for(Particles::iterator it2=voisin.begin();it!=voisin.end();++it){
 denom+=CalculateA(*it,*it2,voisin)*p*(*it2)->GetP1();
 }
}
}

 void Particles::CalculateBetaPart(double &num,bool &b,double alpha){


for(Particles::iterator it=begin();it!=end();++it){
double p=(*it)->GetP1();
(*it)->AddP(alpha*p);
 Particles voisin;
 (*it)->GetVoisin(voisin);
for(Particles::iterator it2=voisin.begin();it!=voisin.end();++it){
(*it)->AddR(-alpha*CalculateA(*it,*it2,voisin)*(*it2)->GetP());
 }
 (*it)->SetZ((*it)->GetR());
 b=(*it)->OKR()&&b;
 num+=(*it)->MultRZ();
 }
 }

void Particles::CalculateP1(double beta){
for(Particles::iterator it=begin();it!=end();++it){
 double p1=(*it)->GetP1();
  double z=(*it)->GetZ();
  (*it)->SetP1(z+beta*p1);
  (*it)->UpdateRZ();
}
}

double CalculateA(const Particle& A,const Particle& B,Particles & voisin){
double ret=0;
if(A->Equal(B)){
for(Particles::iterator it=voisin.begin();it!=voisin.end();++it){
ret+=CalculateABas(A,*it);
}
}else{
ret=-CalculateABas(A,B);
}
return ret;
}

double CalculateABas(const Particle& A,const Particle& B){
physvector<DIM> r=A->GetPos()-B->GetPos();
return (1/A->GetDensity()+1/B->GetDensity())*Kernel_grad_spline5(r,h)*r/r.Norm2()/(A->Distance(B)*(A->GetM()*A->GetDensity()+B->GetM()*B->GetDensity()));
}
