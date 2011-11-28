#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/particles.h"
#include "../../computation/particles_list.h"
#include <deque>
#include <iomanip>
using namespace std;
double eps=1e-10;
#define testing
class ApplyComputeMove_predictorWithoutReduce{
	 Particles_Deque_List& m_vect;
	 double m_Dt;
	 bool m_b;
	public:
	ApplyComputeMove_predictorWithoutReduce( Particles_Deque_List& vect,double dt):m_vect(vect),m_Dt(dt),m_b(false){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		bool b=false;
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->ComputeMove_predictor(m_Dt,b);
			}
		}
		}
};
class Test_Particles_List : public CxxTest::TestSuite
{
public:
Test_Particles_List(){
	#pragma GCC diagnostic ignored "-Wconversion"
	srand ( time(NULL) );
	#pragma GCC diagnostic pop
}
void testCreation_Add(void){
	Particles_List PL;
	deque<ParticleReal> plist;
	double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;

	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
		physvector<3> veps(eps,eps,eps);
	for(map<Key<3>,Particles>::iterator it=PL.m_list.begin();it!=PL.m_list.end();++it){
		for(Particles::iterator it2=it->second.begin();it2!=it->second.end();++it2){
			TS_ASSERT_DELTA((*it2)->GetPos(),physvector< 3  >(x,y,z),veps);
			TS_ASSERT_DELTA((*it2)->GetSpeed(),physvector< 3  >(x2,y2,z2),veps);
		}
	}
}
void testCalculate0Density(void){
	{
	Particles_List PL;
	deque<ParticleReal> plist;
	for(int i=0;i<200;i++){
	double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;

	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
	}
		physvector<3> veps(eps,eps,eps);
		PL.Calculate0Density();
	for(map<Key<3>,Particles>::iterator it=PL.m_list.begin();it!=PL.m_list.end();++it){
		for(Particles::iterator it2=it->second.begin();it2!=it->second.end();++it2){
			TS_ASSERT_DELTA((*it2)->GetMassDensity(),1000,eps);
		}
	}
	}
	
	{
	Particles_List PL;
	Particles_List PL2;
	deque<ParticleReal> plist;
	deque<ParticleReal> plist2;
	for(int i=0;i<200;i++){
	double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;

	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	plist2.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	
	PL.Add( Particle(&plist.back()));
	PL2.Add( Particle(&plist2.back()));
	}
		physvector<3> veps(eps,eps,eps);
	for(map<Key<3>,Particles>::iterator it=PL.m_list.begin();it!=PL.m_list.end();++it){
		it->second.ComputeDensity();
	}
	parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL2.m_vect.size()), ApplyComputeDensity(PL2.m_vect),PL2.m_af);	
	
	for(map<Key<3>,Particles>::iterator it=PL.m_list.begin();it!=PL.m_list.end();++it){
		Particles &it3=PL2.m_list[it->first];
		Particles::iterator it2=it->second.begin();
		Particles::iterator it4=it3.begin();
		while(it2!=it->second.end()){
			TS_ASSERT_DELTA((*it2)->GetDensity(),(*it4)->GetDensity(),eps);
			++it2;++it4;
		}
	}
	}
}
void testUpdate(void){
	Particles_List PL;
	deque<ParticleReal> plist;
	deque<ParticleReal> plist2;
	for(int i=0;i<200;i++){
	double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;

	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	plist2.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
	}
    double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;
	double x3=(rand()%10000)/1000.;
	double y3=(rand()%10000)/1000.;
	double z3=(rand()%10000)/1000.;
	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
	Particle Pupd=Particle(&plist.back());
	Particles* partrem=Pupd->m_container;
	Voisin vois;
	Pupd->GetVoisin(vois);
	Pupd->SetPos(physvector<3>(x3,y3,z3));
	map<Key<DIM> ,Particles>::iterator it=PL.m_list.begin();
   while(it!=PL.m_list.end()){
	   map<Key<DIM> ,Particles>::iterator it2=it;
	   ++it;
        it2->second.Update(&PL);
    }
	PL.m_vect.Update(PL.m_list);
	for(unsigned int i=0;i<plist2.size();++i){
		TS_ASSERT_EQUALS(plist2[i].GetPos(),plist[i].GetPos());
		TS_ASSERT_EQUALS(plist2[i].GetSpeed(),plist[i].GetSpeed());
	}
	
	if(count(PL.m_vect.begin(),PL.m_vect.end(),partrem)==0){
	for(Voisin::iterator_particles it=vois.begin_particles();it!=vois.end_particles();++it){
		if(*it==partrem){
			continue;
		}
		Voisin voistemp=(*it)->GetNeighbour();
		for(Voisin::iterator_particles it2=voistemp.begin_particles();it2!=voistemp.end_particles();++it2){
				TS_ASSERT(*it2!=partrem);
		}
	
	}
	}
	TS_ASSERT_EQUALS(plist[plist2.size()].GetPos(),physvector<3>(x3,y3,z3));
}
void testMove(void){
	Particles_List PL;
	Particles_List PL2;
	deque<ParticleReal> plist;
	deque<ParticleReal> plist2;
	for(int i=0;i<200;i++){
	double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;

	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	plist2.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
	PL2.Add( Particle(&plist2.back()));
	}
	PL.Calculate0Density();
	PL2.Calculate0Density();
	PL.UpdateForce();	
	PL2.UpdateForce();	
	map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();
map<Key<DIM> ,Particles>::iterator it2= PL2.m_list.begin();
physvector<3> veps(eps,eps,eps);
while(it!=PL.m_list.end()){
	TS_ASSERT_EQUALS(it->first,it2->first);
	TS_ASSERT_EQUALS(it->second.size(),it2->second.size());
	Particles::iterator it3=it->second.begin();
	Particles::iterator it4=it2->second.begin();
	while(it3!=it->second.end()){
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it4)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it4)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it4)->GetDensity(),eps);
		++it3;
		++it4;
	}
	++it;
	++it2;	
}
	
	double dt=0.00001;	
for(map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();it!=PL.m_list.end();++it){
	it->second.preComputeMove_predictor(dt);
}
bool b=true;
while(b){
	 b=false;
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL.m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(PL.m_vect),PL.m_af);		
PL.UpdateForce();
for(map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();it!=PL.m_list.end();++it){
	it->second.ComputeMove_predictor(dt,b);
}
}
for(map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();it!=PL.m_list.end();++it){
	it->second.DoMove_predictor();
}

PL2.predictor_corrector_compute(dt);
TS_ASSERT_EQUALS(PL.m_list.size(),PL2.m_list.size());
TS_ASSERT_EQUALS(PL.m_vect.size(),PL2.m_vect.size());
it= PL.m_list.begin();
it2= PL2.m_list.begin();

while(it!=PL.m_list.end()){
	TS_ASSERT_EQUALS(it->first,it2->first);
	TS_ASSERT_EQUALS(it->second.size(),it2->second.size());
	Particles::iterator it3=it->second.begin();
	Particles::iterator it4=it2->second.begin();
	while(it3!=it->second.end()){
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it4)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it4)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it4)->GetDensity(),eps);
		++it3;
		++it4;
	}
	++it;
	++it2;	
}
}
void testMovePart1(void){
	Particles_List PL;
	Particles_List PL2;
	deque<ParticleReal> plist;
	deque<ParticleReal> plist2;
	for(int i=0;i<200;i++){
	double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;

	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	plist2.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
	PL2.Add( Particle(&plist2.back()));
	}
	PL.Calculate0Density();
	PL2.Calculate0Density();
	PL.UpdateForce();	
	PL2.UpdateForce();	
	map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();
map<Key<DIM> ,Particles>::iterator it2= PL2.m_list.begin();
physvector<3> veps(eps,eps,eps);
while(it!=PL.m_list.end()){
	TS_ASSERT_EQUALS(it->first,it2->first);
	TS_ASSERT_EQUALS(it->second.size(),it2->second.size());
	Particles::iterator it3=it->second.begin();
	Particles::iterator it4=it2->second.begin();
	while(it3!=it->second.end()){
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it4)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it4)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it4)->GetDensity(),eps);
		++it3;
		++it4;
	}
	++it;
	++it2;	
}
	
	double dt=0.00001;	
for(map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();it!=PL.m_list.end();++it){
	it->second.preComputeMove_predictor(dt);
}

parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL2.m_vect.size(),CHUNK_SIZE), ApplypreComputeMove_predictor(PL2.m_vect,dt),PL2.m_af);		

TS_ASSERT_EQUALS(PL.m_list.size(),PL2.m_list.size());
TS_ASSERT_EQUALS(PL.m_vect.size(),PL2.m_vect.size());
it= PL.m_list.begin();
it2= PL2.m_list.begin();
while(it!=PL.m_list.end()){
	TS_ASSERT_EQUALS(it->first,it2->first);
	TS_ASSERT_EQUALS(it->second.size(),it2->second.size());
	Particles::iterator it3=it->second.begin();
	Particles::iterator it4=it2->second.begin();
	while(it3!=it->second.end()){
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it4)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it4)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it4)->GetDensity(),eps);
		TS_ASSERT_DELTA((*it3)->m_pos0_5,(*it4)->m_pos0_5,veps);
		TS_ASSERT_DELTA((*it3)->m_speed0_5,(*it4)->m_speed0_5,veps);
		++it3;
		++it4;
	}
	++it;
	++it2;	
}
}
void testMovePart2(void){
	Particles_List PL;
	Particles_List PL2;
	Particles_List PL3;
	deque<ParticleReal> plist;
	deque<ParticleReal> plist2;
	deque<ParticleReal> plist3;
	for(int i=0;i<2;i++){
	double x=(rand()%10000)/10000.;
	double y=(rand()%10000)/10000.;
	double z=(rand()%10000)/10000.;
	double x2=(rand()%10000)/10000.;
	double y2=(rand()%10000)/10000.;
	double z2=(rand()%10000)/10000.;

	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	plist2.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	plist3.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
	PL2.Add( Particle(&plist2.back()));
	PL3.Add( Particle(&plist3.back()));
	}
	PL.Calculate0Density();
	PL2.Calculate0Density();
	PL3.Calculate0Density();
	PL.UpdateForce();	
	PL2.UpdateForce();	
	PL3.UpdateForce();	
	map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();
map<Key<DIM> ,Particles>::iterator it2= PL2.m_list.begin();
map<Key<DIM> ,Particles>::iterator it5= PL3.m_list.begin();
physvector<3> veps(eps,eps,eps);
while(it!=PL.m_list.end()){
	TS_ASSERT_EQUALS(it->first,it2->first);
	TS_ASSERT_EQUALS(it->first,it5->first);
	TS_ASSERT_EQUALS(it->second.size(),it2->second.size());
	TS_ASSERT_EQUALS(it->second.size(),it5->second.size());
	Particles::iterator it3=it->second.begin();
	Particles::iterator it4=it2->second.begin();
	Particles::iterator it6=it5->second.begin();
	while(it3!=it->second.end()){
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it4)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it4)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it4)->GetDensity(),eps);
		
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it6)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it6)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it6)->GetDensity(),eps);
		++it3;
		++it4;
		++it6;
	}
	++it;
	++it2;	
	++it5;
}
	
	double dt=0.001;	
for(map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();it!=PL.m_list.end();++it){
	it->second.preComputeMove_predictor(dt);
}
bool b=true;
int nb1=0;
while(b){
	 b=false;
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL.m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(PL.m_vect),PL.m_af);		
PL.UpdateForce();
for(map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();it!=PL.m_list.end();++it){
	it->second.ComputeMove_predictor(dt,b);
}
++nb1;
}
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL2.m_vect.size(),CHUNK_SIZE), ApplypreComputeMove_predictor(PL2.m_vect,dt),PL2.m_af);		
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL3.m_vect.size(),CHUNK_SIZE), ApplypreComputeMove_predictor(PL3.m_vect,dt),PL3.m_af);		
	
b=true;
int nb2=0;
while(b){
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL2.m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(PL2.m_vect),PL2.m_af);		
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL3.m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(PL3.m_vect),PL3.m_af);		
PL2.UpdateForce();
PL3.UpdateForce();
ApplyComputeMove_predictor ap(PL2.m_vect,dt);
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL3.m_vect.size(),CHUNK_SIZE), ApplyComputeMove_predictorWithoutReduce(PL3.m_vect,dt),PL3.m_af);		
parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,PL2.m_vect.size(),CHUNK_SIZE),ap,PL2.m_af);		
b=ap.GetB();
++nb2;
}
TS_ASSERT_EQUALS(nb1,nb2);
TS_ASSERT_EQUALS(PL.m_list.size(),PL2.m_list.size());
TS_ASSERT_EQUALS(PL.m_vect.size(),PL2.m_vect.size());
it= PL.m_list.begin();
it2= PL2.m_list.begin();
it5= PL3.m_list.begin();
while(it!=PL.m_list.end()){
	TS_ASSERT_EQUALS(it->first,it2->first);
	TS_ASSERT_EQUALS(it->first,it5->first);
	TS_ASSERT_EQUALS(it->second.size(),it2->second.size());
	TS_ASSERT_EQUALS(it->second.size(),it5->second.size());
	Particles::iterator it3=it->second.begin();
	Particles::iterator it4=it2->second.begin();
	Particles::iterator it6=it5->second.begin();
	while(it3!=it->second.end()){
	    TS_ASSERT_DELTA((*it3)->GetPos(),(*it4)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it4)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it4)->GetDensity(),eps);
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it6)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it6)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it6)->GetDensity(),eps);
		++it3;
		++it4;
		++it6;
	}
	++it;
	++it2;
	++it5;
}
}

void testMoveBeeman(void){
	Particles_List PL;
	Particles_List PL2;
	deque<ParticleReal> plist;
	deque<ParticleReal> plist2;
	for(int i=0;i<200;i++){
	double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;

	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	plist2.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
	PL2.Add( Particle(&plist2.back()));
	}
	PL.Calculate0Density();
	PL2.Calculate0Density();
	PL.UpdateForce();	
	PL2.UpdateForce();	
	map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();
map<Key<DIM> ,Particles>::iterator it2= PL2.m_list.begin();
physvector<3> veps(eps,eps,eps);
while(it!=PL.m_list.end()){
	TS_ASSERT_EQUALS(it->first,it2->first);
	TS_ASSERT_EQUALS(it->second.size(),it2->second.size());
	Particles::iterator it3=it->second.begin();
	Particles::iterator it4=it2->second.begin();
	while(it3!=it->second.end()){
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it4)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it4)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it4)->GetDensity(),eps);
		++it3;
		++it4;
	}
	++it;
	++it2;	
}

double dt=0.0001;
for(map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();it!=PL.m_list.end();++it){
	it->second.Beeman_first_time(dt);
}

PL2.beeman_compute(dt);
TS_ASSERT_EQUALS(PL.m_list.size(),PL2.m_list.size());
TS_ASSERT_EQUALS(PL.m_vect.size(),PL2.m_vect.size());
it= PL.m_list.begin();
it2= PL2.m_list.begin();

while(it!=PL.m_list.end()){
	TS_ASSERT_EQUALS(it->first,it2->first);
	TS_ASSERT_EQUALS(it->second.size(),it2->second.size());
	Particles::iterator it3=it->second.begin();
	Particles::iterator it4=it2->second.begin();
	while(it3!=it->second.end()){
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it4)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it4)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it4)->GetDensity(),eps);
		++it3;
		++it4;
	}
	++it;
	++it2;	
}

parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL.m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(PL.m_vect),PL.m_af);		
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL2.m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(PL2.m_vect),PL2.m_af);		
PL.UpdateForce();
PL2.UpdateForce();
for(map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();it!=PL.m_list.end();++it){
	it->second.Beeman_precompute(dt);
}
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,PL.m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(PL.m_vect),PL.m_af);		
PL.UpdateForce();
for(map<Key<DIM> ,Particles>::iterator it= PL.m_list.begin();it!=PL.m_list.end();++it){
	it->second.Beeman_compute(dt);
}

PL2.beeman_compute(dt);

TS_ASSERT_EQUALS(PL.m_list.size(),PL2.m_list.size());
TS_ASSERT_EQUALS(PL.m_vect.size(),PL2.m_vect.size());
it= PL.m_list.begin();
it2= PL2.m_list.begin();

while(it!=PL.m_list.end()){
	TS_ASSERT_EQUALS(it->first,it2->first);
	TS_ASSERT_EQUALS(it->second.size(),it2->second.size());
	Particles::iterator it3=it->second.begin();
	Particles::iterator it4=it2->second.begin();
	while(it3!=it->second.end()){
		TS_ASSERT_DELTA((*it3)->GetPos(),(*it4)->GetPos(),veps);
		TS_ASSERT_DELTA((*it3)->GetSpeed(),(*it4)->GetSpeed(),veps);
		TS_ASSERT_DELTA((*it3)->GetDensity(),(*it4)->GetDensity(),eps);
		++it3;
		++it4;
	}
	++it;
	++it2;	
}
}
};