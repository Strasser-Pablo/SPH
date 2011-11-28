#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/particles.h"
#include "../../computation/particles_list.h"
#include <deque>
using namespace std;
double eps=1e-10;
#define testing
class Test_Particles : public CxxTest::TestSuite
{
public:
Test_Particles(){
	#pragma GCC diagnostic ignored "-Wconversion"
	srand ( time(NULL) );
	#pragma GCC diagnostic pop
}
void testUpdate(void){
	{
	double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;
	double x3=(rand()%10000)/1000.;
	double y3=(rand()%10000)/1000.;
	double z3=(rand()%10000)/1000.;
 physvector<3>v3(x3,y3,z3);
	Particles_List PL;
	deque<ParticleReal> plist;
	plist.push_front(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.front()));
	for(map<Key<3>,Particles>::iterator it=PL.m_list.begin();it!=PL.m_list.end();++it){
		for(Particles::iterator it2=it->second.begin();it2!=it->second.end();++it2){
			(*it2)->SetPos(v3);
		}
	}
	
	for(map<Key<3>,Particles>::iterator it=PL.m_list.begin();it!=PL.m_list.end();++it){
		it->second.Update(&PL);
	}
	physvector<3> veps(eps,eps,eps);
	int k=0;
	for(map<Key<3>,Particles>::iterator it=PL.m_list.begin();it!=PL.m_list.end();++it){
		for(Particles::iterator it2=it->second.begin();it2!=it->second.end();++it2){
			TS_ASSERT_DELTA((*it2)->GetPos(),physvector< 3  >(x3,y3,z3),veps);
			++k;
		}
	}
	TS_ASSERT_EQUALS(k,1);
	}
	
{   
	double x=(rand()%10000)/1000.;
	double y=(rand()%10000)/1000.;
	double z=(rand()%10000)/1000.;
	double x2=(rand()%10000)/1000.;
	double y2=(rand()%10000)/1000.;
	double z2=(rand()%10000)/1000.;
	double x3=(rand()%10000)/1000.;
	double y3=(rand()%10000)/1000.;
	double z3=(rand()%10000)/1000.;
 physvector<3>v3(x3,y3,z3);
 physvector<3>v1(x,y,z);
	Particles_List PL;
	deque<ParticleReal> plist;
	plist.push_back(ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
		plist.push_back(ParticleReal(physvector< 3  >(x3,y3,z3),physvector< 3  >(x2,y2,z2),water));
	PL.Add( Particle(&plist.back()));
	plist[0].SetPos(v3);
	plist[1].SetPos(v1);
	
	for(map<Key<3>,Particles>::iterator it=PL.m_list.begin();it!=PL.m_list.end();++it){
		it->second.Update(&PL);
	}
	physvector<3> veps(eps,eps,eps);
	int k=0;
	for(map<Key<3>,Particles>::iterator it=PL.m_list.begin();it!=PL.m_list.end();++it){
		for(Particles::iterator it2=it->second.begin();it2!=it->second.end();++it2){
			++k;
		}
		TS_ASSERT(!it->second.GetMussBeDeleted());
	}
	TS_ASSERT_EQUALS(k,2);
}
}
void testRemoveNeighbour(void){
	Particles * P1=new Particles;
	Particles * P2=new Particles;
	Particles * P3=new Particles;
	Particles * P4=new Particles;
	list<Particles *> listvois;
	listvois.push_back(P1);
	listvois.push_back(P2);
	listvois.push_back(P3);
	listvois.push_back(P4);
	Voisin vois(listvois);
	P1->SetNeighbour(vois);
	P1->RemoveParticlesNeighbour(P2);
	Voisin vois2=P1->GetNeighbour();
	list<Particles *> listvois2=vois2.GetParticlesVect();
	TS_ASSERT_EQUALS(listvois2.size(),3);
	TS_ASSERT_EQUALS(count(vois2.begin_particles(),vois2.end_particles(),P2),0);
	TS_ASSERT_EQUALS(count(vois2.begin_particles(),vois2.end_particles(),P1),1);
	TS_ASSERT_EQUALS(count(vois2.begin_particles(),vois2.end_particles(),P3),1);
	TS_ASSERT_EQUALS(count(vois2.begin_particles(),vois2.end_particles(),P4),1);
	
}
};