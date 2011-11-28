#include <cxxtest/TestSuite.h>
#include <cstdlib>
#include <time.h>
#include "../../computation/voisin.h"
#include "../../computation/particles.h"
class Test_Voisin : public CxxTest::TestSuite
{
public:
Test_Voisin(){
	#pragma GCC diagnostic ignored "-Wconversion"
	srand ( time(NULL) );
	#pragma GCC diagnostic pop
}
void testCreation(void){

	Voisin v;
	list<Particles*>listvois= v.GetParticlesVect();
	TS_ASSERT(listvois.empty());
	
	list<Particles*>listvois2;
	Particles * P1=new Particles;
	Particles * P2=new Particles;
	Particles PComp1=*P1;
	Particles PComp2=*P2;
	TS_ASSERT_EQUALS(PComp1,*P1);
	listvois2.push_back(P1);
	listvois2.push_back(P2);
	Voisin v2(listvois2);
	list<Particles*>listvoisres= v2.GetParticlesVect();
	Particles *Pres1=listvoisres.front();
	listvoisres.pop_front();
	Particles *Pres2=listvoisres.front();
	listvoisres.pop_front();
	TS_ASSERT_EQUALS(P1,Pres1);
	TS_ASSERT_EQUALS(P2,Pres2);
	TS_ASSERT(listvoisres.empty());
	TS_ASSERT_EQUALS(PComp1,*Pres1);
	TS_ASSERT_EQUALS(PComp2,*Pres2);
	TS_ASSERT_EQUALS(Particles(),*Pres1);
	TS_ASSERT_EQUALS(Particles(),*Pres2);
	delete P1;
	delete P2;
}
void testErase(void){
	list<Particles*>listvois;
	Particles * P1=new Particles;
	Particles * P2=new Particles;
	Particles PComp1=*P1;
	Particles PComp2=*P2;
	listvois.push_back(P1);
	listvois.push_back(P2);
	Voisin v(listvois);
	Voisin::iterator_particles it=v.begin_particles();
	v.erase(it);
	list<Particles*>listvoisres= v.GetParticlesVect();
	Particles *Pres1=listvoisres.front();
	listvoisres.pop_front();
	TS_ASSERT_EQUALS(Pres1,P2);
	TS_ASSERT_EQUALS(*Pres1,PComp2);
	TS_ASSERT(listvoisres.empty());
	delete P1;
	delete P2;
}
void testParticles_Iterator(void){
	list<Particles*>listvois;
	Particles * P1=new Particles;
	Particles * P2=new Particles;
	Particles PComp1=*P1;
	Particles PComp2=*P2;
	listvois.push_back(P1);
	listvois.push_back(P2);
	Voisin v(listvois);
	Voisin::iterator_particles itbeg=v.begin_particles();
	Voisin::iterator_particles itend=v.end_particles();
	--itend;
	TS_ASSERT_EQUALS(*itbeg,P1);
	TS_ASSERT_EQUALS(**itbeg,PComp1);
	TS_ASSERT_EQUALS(*itend,P2);
	TS_ASSERT_EQUALS(**itend,PComp2);
	delete P1;
	delete P2;
}

void testEmpty_iterator(void){
	list<Particles*>listEmpty;
	Voisin vEmpty(listEmpty);
	Voisin::iterator_particles itEmptybeg=vEmpty.begin_particles();
	Voisin::iterator_particles itEmptyend=vEmpty.end_particles();
	Voisin::iterator itEmptyPbeg=vEmpty.begin();
	Voisin::iterator itEmptyPend=vEmpty.end();
	TS_ASSERT_EQUALS(itEmptybeg,itEmptyend);
	TS_ASSERT(!(itEmptybeg!=itEmptyend));
	TS_ASSERT_EQUALS(itEmptyPbeg,itEmptyPend);
	TS_ASSERT(!(itEmptyPbeg!=itEmptyPend));
	
	list<Particles*>listEmpty2;
	Particles * P1=new Particles;
	listEmpty2.push_back(P1);
	Voisin vEmpty2(listEmpty2);
	Voisin::iterator_particles itEmpty2beg=vEmpty2.begin_particles();
	Voisin::iterator_particles itEmpty2end=vEmpty2.end_particles();
	Voisin::iterator itEmpty2Pbeg=vEmpty2.begin();
	Voisin::iterator itEmpty2Pend=vEmpty2.end();
	TS_ASSERT(!(itEmpty2beg==itEmpty2end));
	TS_ASSERT(itEmpty2beg!=itEmpty2end);
	TS_ASSERT_EQUALS(itEmpty2Pbeg,itEmpty2Pend);
	TS_ASSERT(!(itEmpty2Pbeg!=itEmpty2Pend));
	delete P1;
}
void testIncrementIterator(void){
	list<Particles*>lis;
	Particles * P1=new Particles;
	Particles * P2=new Particles;
	double x=rand()/1000.;
	double y=rand()/1000.;
	double z=rand()/1000.;
	double x2=rand()/1000.;
	double y2=rand()/1000.;
	double z2=rand()/1000.;
	ParticleReal* Pr1=new ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	Particle Pa1(Pr1);
	P1->Add(Pa1);
	 x=rand()/1000.;
	 y=rand()/1000.;
	 z=rand()/1000.;
	 x2=rand()/1000.;
	 y2=rand()/1000.;
	 z2=rand()/1000.;
	 ParticleReal* Pr2=new ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	Particle Pa2(Pr2);
	P1->Add(Pa2);
	
	 x=rand()/1000.;
	 y=rand()/1000.;
	 z=rand()/1000.;
	 x2=rand()/1000.;
	 y2=rand()/1000.;
	 z2=rand()/1000.;
	ParticleReal* Pr3=new ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	Particle Pa3(Pr3);
	P1->Add(Pa3);
	 
	 x=rand()/1000.;
	 y=rand()/1000.;
	 z=rand()/1000.;
	 x2=rand()/1000.;
	 y2=rand()/1000.;
	 z2=rand()/1000.;
	 ParticleReal* Pr4=new ParticleReal(physvector< 3  >(x,y,z),physvector< 3  >(x2,y2,z2),water);
	Particle Pa4(Pr4);
	P2->Add(Pa4);
	
	lis.push_back(P1);
	lis.push_back(P2);
	Voisin v(lis);
	Voisin::iterator it=v.begin();
	TS_ASSERT(it!=v.end());
	TS_ASSERT(!(it==v.end()));
	TS_ASSERT_EQUALS(*it,Pa1);
	TS_ASSERT_EQUALS(**it,Pr1);
	++it;
	TS_ASSERT(it!=v.end());
	TS_ASSERT(!(it==v.end()));
	TS_ASSERT_EQUALS(*it,Pa2);
	TS_ASSERT_EQUALS(**it,Pr2);
	++it;
	TS_ASSERT(it!=v.end());
	TS_ASSERT(!(it==v.end()));
	TS_ASSERT_EQUALS(*it,Pa3);
	TS_ASSERT_EQUALS(**it,Pr3);
	++it;
	TS_ASSERT(it!=v.end());
	TS_ASSERT(!(it==v.end()));
	TS_ASSERT_EQUALS(*it,Pa4);
	TS_ASSERT_EQUALS(**it,Pr4);
	++it;
	TS_ASSERT(!(it!=v.end()));
	TS_ASSERT((it==v.end()));
	
	
	Voisin::const_iterator it2=v.begin();
	TS_ASSERT(it2!=v.end());
	TS_ASSERT(!(it2==v.end()));
	TS_ASSERT_EQUALS(*it2,Pa1);
	TS_ASSERT_EQUALS(**it2,Pr1);
	++it2;
	TS_ASSERT(it2!=v.end());
	TS_ASSERT(!(it2==v.end()));
	TS_ASSERT_EQUALS(*it2,Pa2);
	TS_ASSERT_EQUALS(**it2,Pr2);
	++it2;
	TS_ASSERT(it2!=v.end());
	TS_ASSERT(!(it2==v.end()));
	TS_ASSERT_EQUALS(*it2,Pa3);
	TS_ASSERT_EQUALS(**it2,Pr3);
	++it2;
	TS_ASSERT(it2!=v.end());
	TS_ASSERT(!(it2==v.end()));
	TS_ASSERT_EQUALS(*it2,Pa4);
	TS_ASSERT_EQUALS(**it2,Pr4);
	++it2;
	TS_ASSERT(!(it2!=v.end()));
	TS_ASSERT((it2==v.end()));
	delete P1;
	delete P2;
	delete Pr1;
	delete Pr2;
	delete Pr3;
	delete Pr4;
}
};