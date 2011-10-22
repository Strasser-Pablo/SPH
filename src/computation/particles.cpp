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
#include <algorithm>
using namespace std;


Particles::Particles(ParticleType type): list<Particle>(),m_type(type)
{

}

Particles::Particles(Key<DIM> & K):m_key(K)
{

}

Particles::Particles(const Particles& A):m_type(A.m_type),list<Particle>(A){

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

list<Particles*> Particles::GetNeighbour()const{
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
 if(empty()){
	 plist->RemoveParticles(this);
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
	if(!(*it)->GetBoundary()){
    double b=(*it)->GetB();
    (*it)->SetP(0);
	(*it)->SetR(0);
(*it)->SetRprec(b);
(*it)->SetZprec(b);
(*it)->SetP1(b);
}
}
}

  void Particles::CalculateAlphaPart(double &num,double &denom){
for(Particles::iterator it=begin();it!=end();++it){
	if(!(*it)->GetBoundary()){
 num+=(*it)->MultRZprec();
 Particles voisin;
 (*it)->GetVoisin(voisin);
 double p=(*it)->GetP1();
 for(Particles::iterator it2=voisin.begin();it2!=voisin.end();++it2){
	 if(!(*it2)->GetBoundary()){
 denom+=(*it)->CalculateA(*it2,voisin)*p*(*it2)->GetP1();
	 }
 }
}
}
}

 void Particles::CalculateBetaPart(double &num,bool &b,double alpha){


for(Particles::iterator it=begin();it!=end();++it){
	if(!(*it)->GetBoundary()){
double p=(*it)->GetP1();
(*it)->AddP(alpha*p);
 Particles voisin;
 (*it)->GetVoisin(voisin);
 (*it)->SetR((*it)->GetRprec());
for(Particles::iterator it2=voisin.begin();it2!=voisin.end();++it2){
	 if(!(*it2)->GetBoundary()){
(*it)->AddR(-alpha*(*it)->CalculateA(*it2,voisin)*(*it2)->GetP1());
 }
}
 (*it)->SetZ((*it)->GetR());
 b=(*it)->OKR()&&b;
 num+=(*it)->MultRZ();
 }
}
 }

void Particles::CalculateP1(double beta){
for(Particles::iterator it=begin();it!=end();++it){
	if(!(*it)->GetBoundary()){
 double p1=(*it)->GetP1();
  double z=(*it)->GetZ();
  (*it)->SetP1(z+beta*p1);
  (*it)->UpdateRZ();
}
}
}

void Particles::SetB_Speed(){
for(Particles::iterator it=begin();it!=end();++it){
		 if(!(*it)->GetBoundary()){
 (*it)->SetB_Speed();
		 }
}
}


void Particles::PreparePosition(bool& b){
for(Particles::iterator it=begin();it!=end();++it){
		 if(!(*it)->GetBoundary()){
 (*it)->PreparePosition(b);
		 }
 }
}

void Particles::Calculate0Density(){
	for(Particles::iterator it=begin();it!=end();++it){
		 if(!(*it)->GetBoundary()){
 (*it)->Calculate0Density();
		 }
 }
}

Boundaries<DIM> Particles::GetBoundary()const{
	return m_boundary;
}
	void Particles::SetBoundary(Boundaries<DIM> & b){
		m_boundary=b;
	}


void Particles::SetKey(Key<DIM> & k){
	m_key=k;
}
Key<DIM> Particles::GetKey()const{
	return m_key;
}


void Particles::RemoveParticlesNeighbour(const Particles * part){
	for(list<Particles*>::iterator it=m_neighbour.begin();it!=m_neighbour.end();it++)
	{if(*it==part){
		m_neighbour.erase(it);
	}
	}
	Key<DIM> k1=part->GetKey();
	Key<DIM> k2=GetKey();
	m_boundary.RemoveBoundary(k2,k1);
}