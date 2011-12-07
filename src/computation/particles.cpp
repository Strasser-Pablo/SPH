/*
   Code écrit par Pablo Strasser dans le cadre d'un travail de Master bi-disiplinaire
 */
/** \file particles.cpp
 * @brief Implementation file for particles.
 *
 */
#include <cstdio>
#include "particle.h"
#include "particles.h"

#include "particles_list.h"
#include "debug.h"
#include <algorithm>

using namespace std;


Particles::Particles(ParticleType type) : list<Particle>(),m_b_muss_be_deleted(false),m_type(type)
{

}

Particles::Particles(Key<DIM> & K) : m_b_muss_be_deleted(false),m_key(K)
{

}

Particles::Particles(const Particles& A) : list<Particle>(A),m_b_muss_be_deleted(false),m_type(A.m_type){

}

Particles::Particles() : m_b_muss_be_deleted(false),m_type(none)
{

}


void Particles::ComputeDensity()
{
	//ProfilerFlush();
	//GetKey().Dump();
	for (list<Particle>::iterator it=begin(); it!=end(); ++it) {
		(*it)->ComputeDensity();
	}
}


void Particles::SetNeighbour(Voisin& list )
{
	m_neighbour=list;
}

Voisin Particles::GetNeighbour() const {
	return m_neighbour;
}

#ifdef PRESSURE_LAPLACIEN
	bool Particles::PreComputeMove(double dt)
	{
		//ProfilerFlush();
		bool ret=false;
		for (list<Particle>::iterator it=begin(); it!=end(); ++it) {
			ret=(*it)->PreComputeMove( dt)|| ret;
		}
		return ret;
	}
#endif
void Particles::ComputeMove(double dt)
{
	//ProfilerFlush();
	for (list<Particle>::iterator it=begin(); it!=end(); ++it) {
		(*it)->ComputeMove( dt);
	}
}

void Particles::Update( Particles_List*  plist)
{
	//ProfilerFlush();
	list<Particle>::iterator it=begin();
	while (it!=end()) {
		//iterator effectly used
		list<Particle>::iterator it2=it;
		//we increase the iterator before that we splice to don't have problem when it2 is invalided
		it++;
		plist->Update(it2,this);
	}
	//If empty mark for deletion. The removing of neighbour reference is done only
	// At deletion time, to protect from particle that enter after to be marked.
	if(empty()) {
		SetMussBeDeleted(true);
	}
}

/*bool Particles::operator==(const Particles& parts) const
   {
   return *(this::list<Particle>)==parts::list<Particle>;
   }*/


void Particles::Dump(bool voisin)
{
	cout<<"begin Particles"<<endl;
	for(Particles::iterator it=begin(); it!=end(); ++it) {
		(*it)->Dump();
	}
	if(voisin) {
		cout<<"dump of neighbour"<<endl;
		//todo correct it
		//DumpNeighbour(m_neighbour);
		cout<<"end dump of neighbour"<<endl;
	}
	cout<<"end Particles"<<endl;
}

void Particles::Add(Particle part){
	part->SetContainerParticles(this);
	push_back(part);
}
#ifdef PRESSURE_LAPLACIEN
	void Particles::InitializeCG(){
		for(Particles::iterator it=begin(); it!=end(); ++it) {
			if(!(*it)->GetBoundary()) {
				double b=(*it)->GetB();
				 (*it)->SetP(0);
				(*it)->SetR(0);
				(*it)->SetRprec(b);
				for(Voisin::iterator it2=m_neighbour.begin(); it2!=m_neighbour.end(); ++it2) {
					if(!(*it2)->GetBoundary()) {
						(*it)->AddRprec(-(*it)->CalculateA(*it2)*(*it2)->GetP());
					}
				}
				(*it)->SetZprec((*it)->GetRprec());
				(*it)->SetP1((*it)->GetRprec());

			}
		}
	}

	void Particles::CalculateAlphaPart(double &num,double &denom){
		for(Particles::iterator it=begin(); it!=end(); ++it) {
			if(!(*it)->GetBoundary()) {
				num+=(*it)->MultRZprec();

				double p=(*it)->GetP1();
				for(Voisin::iterator it2=m_neighbour.begin(); it2!=m_neighbour.end(); ++it2) {
					if(!(*it2)->GetBoundary()) {
						denom+=(*it)->CalculateA(*it2)*p*(*it2)->GetP1();
					}
				}
			}
		}

	}

	void Particles::CalculateBetaPart(double &num,double alpha,bool &b){


		for(Particles::iterator it=begin(); it!=end(); ++it) {
			if(!(*it)->GetBoundary()) {
				double p=(*it)->GetP1();
				(*it)->AddP(alpha*p);
				(*it)->SetR((*it)->GetRprec());
				for(Voisin::iterator it2=m_neighbour.begin(); it2!=m_neighbour.end(); ++it2) {
					if(!(*it2)->GetBoundary()) {
						(*it)->AddR(-alpha*(*it)->CalculateA(*it2)*(*it2)->GetP1());
					}
				}
				(*it)->SetZ((*it)->GetR());
				num+=(*it)->MultRZ();
				b=b&&(*it)->OKR();
			}
		}
	}

	void Particles::CalculateP1(double beta){
		for(Particles::iterator it=begin(); it!=end(); ++it) {
			if(!(*it)->GetBoundary()) {
				double p1=(*it)->GetP1();
				double z=(*it)->GetZ();
				(*it)->SetP1(z+beta*p1);
				(*it)->UpdateRZ();
			}
		}
	}

	void Particles::SetB_Speed(){
		for(Particles::iterator it=begin(); it!=end(); ++it) {
			(*it)->SetB_Speed();
		}
	}


	void Particles::PreparePosition(bool& b){
		for(Particles::iterator it=begin(); it!=end(); ++it) {
			(*it)->PreparePosition(b);
		}
	}
#endif
void Particles::Calculate0Density(double &m){
	for(Particles::iterator it=begin(); it!=end(); ++it) {
		(*it)->Calculate0Density(m);
	}
}





void Particles::SetKey(Key<DIM> & k){
	m_key=k;
}
Key<DIM> Particles::GetKey() const {
	return m_key;
}


void Particles::RemoveParticlesNeighbour(const Particles * part){
	Voisin::iterator_particles it=m_neighbour.begin_particles();
	while(it!=m_neighbour.end_particles())
	{
		//Second iterator because in deleting we invalidate the previous iterator
		Voisin::iterator_particles it2=it;
		++it;
		if(*it2==part) {
			m_neighbour.erase(it2);
		}
	}
}

void Particles::GetNeighbour(Voisin *& vois){
	vois=&m_neighbour;
}


#ifdef PRESSURE_LAPLACIEN
	bool Particles::FindBoundary(bool b) {
		if(empty()) {
			return false;
		}
		else{
			for(Particles::iterator it=begin(); it!=end(); it++) {
				(*it)->SetBoundary(false);
			}
			if(b) {
				(*begin())->SetBoundary(true);
			}
			return true;
		}
	}
#endif
void Particles::WritePos(fstream& out) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->WritePos( out);
	}
}

void Particles::Density(fstream &out) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		out<<(*it)->GetDensity()<<endl;
	}
}

void Particles::Pressures(fstream &out) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		out<<(*it)->GetPressure()<<endl;
	}
}

void Particles::Mass(fstream &out) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		out<<(*it)->GetMass()<<endl;
	}
}

void Particles::MassDensity(fstream &out) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		out<<(*it)->GetMassDensity()<<endl;
	}
}

void Particles::preComputeMove_predictor(double dt){
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->preComputeMove_predictor(dt);
	}
}
void Particles::ComputeMove_predictor(double dt,bool &b){
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->ComputeMove_predictor(dt,b);
	}
}
void Particles::DoMove_predictor(){
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->DoMove_predictor();
	}
}
void Particles::NB_it(fstream& out) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		out<<(*it)->GetNb_It()<<endl;
	}
}

void Particles::NextForceTimeStep(double &dt) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->NextForceTimeStep(dt);
	}
}


void Particles::NextCourantVisciousTimeStep(double &dt) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->NextCourantVisciousTimeStep(dt);
	}
}

void Particles::CalculateSubGridTens() {
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->CalculateSubGridTens();
	}
}

void Particles::WriteSpeed(fstream & out) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->WriteSpeed(out);
	}
}

void Particles::UpdateForce() const {
	//ProfilerFlush();
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->UpdateForce();
	}
}

void Particles::WriteErf(fstream & out,double t) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->WriteErf(out,t);
	}
}

void Particles::WriteForce(fstream & out) const {
	for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->WriteForce(out);
	}
}
	void Particles::WriteForceViscosity(fstream & out) const {
		for(Particles::const_iterator it=begin(); it!=end(); it++) {
			(*it)->WriteForceViscosity(out);
		}
	}

	void Particles::WriteForceGravity(fstream & out) const {
		for(Particles::const_iterator it=begin(); it!=end(); it++) {
			(*it)->WriteForceGravity(out);
		}
	}

	void Particles::WriteForcePressure(fstream & out) const {
		for(Particles::const_iterator it=begin(); it!=end(); it++) {
			(*it)->WriteForcePressure(out);
		}
	}

	void Particles::WriteForceTurbulence(fstream & out) const {
		for(Particles::const_iterator it=begin(); it!=end(); it++) {
			(*it)->WriteForceTurbulence(out);
		}
	}
void Particles::SetMussBeDeleted(bool b){
	m_b_muss_be_deleted=b;
}
bool Particles::GetMussBeDeleted(){
	return m_b_muss_be_deleted;
}

void Particles::Beeman_compute(double dt){
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->Beeman_compute(dt);
	}
}
void Particles::Beeman_precompute(double dt){
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->Beeman_precompute(dt);
	}
}

void Particles::Beeman_first_time(double dt){
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->Beeman_first_time(dt);
	}
}
void Particles::WriteMussBeDeleted(fstream &out) const {
	out<<m_b_muss_be_deleted;
}

void Particles::SetToMeanMass() {
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->SetToMeanMass();
	}
}

void Particles::CorrectPosition(){
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->CorrectPosition();
	}
};

void Particles::CorrectSpeed(){
	for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->CorrectSpeed();
	}	
};
void Particles::PrepareSpeed(){
		for(Particles::iterator it=begin(); it!=end(); it++) {
		(*it)->PrepareSpeed();
	}
};

	void Particles::WritePressuresPos(fstream & out)const{
		for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->WritePressuresPos(out);
	}
	}
	void Particles::WritePressuresSpeed(fstream &out)const{
		for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->WritePressuresSpeed(out);
	}
	}
	
	void Particles::WriteNbItPos(fstream &out)const{
		for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->WriteNbItPos(out);
	}
	}
	void Particles::WriteNbItSpeed(fstream &out)const{
		for(Particles::const_iterator it=begin(); it!=end(); it++) {
		(*it)->WriteNbItSpeed(out);
	}
	}
	
	double Particles::TestSpeedOK(bool &b){
		double ret=100000;
		for(Particles::iterator it=begin(); it!=end(); it++) {
		double temp=(*it)->TestSpeedOK(b);
		if(temp<ret){
			ret=temp;
		}
	}
	return ret;
	};
	double Particles::TestPositionOK(bool &b){
		double ret=100000;
		for(Particles::iterator it=begin(); it!=end(); it++) {
		double temp=(*it)->TestPositionOK(b);
		if(temp<ret){
			ret=temp;
		}
	}
	return ret;
	};