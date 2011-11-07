#include "particles_list.h"
#include "const.h"
  

Particles_List::Particles_List():m_t(0),m_n(0)
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


 void Particles_List::InitializeCG(){
  for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.InitializeCG();
    }
}

double Particles_List::CalculateAlpha(double &num,bool &b){
    double denom=0;
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.CalculateAlphaPart(num,denom);
    }
	b=num==0 && denom==0;
return num/denom;
}

double Particles_List::CalculateBeta(double &denom,bool &bret,double alpha){
    double num=0;
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
bool b;
int j=0;
while(!bcont){
    double num=0;
	cout<<"loop"<<endl;
double alpha=CalculateAlpha(num,b);
if(b){
	break;
}
double beta=CalculateBeta(num,bcont,alpha);
CalculateP1(beta);
j++;
cout<<"end loop"<<endl;
}
cout<<"conjugate gradient nb it "<<j<<endl;
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

void Particles_List::Calculate0Density(){
	 for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
		it->second.ComputeDensity();
    }
	for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.Calculate0Density();
    }
}

void Particles_List::FindBoundary(){
bool b=false;
	for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
b=it->second.FindBoundary(!b);
}
}

void Particles_List::predictor_corrector_compute(double DT){
	for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
it->second.preComputeMove_predictor(DT);
}

bool b=true;
while(b){
	b=false;
UpdateForce();
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
it->second.ComputeMove_predictor(DT,b);
}
}
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
it->second.DoMove_predictor();
}
}

double Particles_List::NextTimeStep()const{
	double dt=DT;
	UpdateForce();
	for (map<Key<DIM> ,Particles>::const_iterator it=m_list.begin();it!=m_list.end();it++) {
it->second.NextForceTimeStep(dt);;
}
	for (map<Key<DIM> ,Particles>::const_iterator it=m_list.begin();it!=m_list.end();it++) {
it->second.NextCourantVisciousTimeStep(dt);
}	
return 0.3*dt;	
}


void Particles_List::UpdateForce()const{
		for (map<Key<DIM> ,Particles>::const_iterator it=m_list.begin();it!=m_list.end();it++) {
it->second.UpdateForce();
}
}