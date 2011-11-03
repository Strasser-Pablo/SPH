#include "world_test.h"
/**
* \file world_test.cpp Implementation file for World_test.
**/


World_test::World_test()
{

}

void World_test::Do()
{
double uy=1;

int Nx=10;
int Ny=3;
int Nz=10;

vector<vector<Particle> > listvect(Ny);
for(int j=0;j<Ny;j++){
	vector<Particle> begvect(Nx*Nz);
for(int i=0;i<Nx;i++){
	
		for(int k=0;k<Nz;k++){
			Add(ParticleReal(physvector< 3  >(i*h/3,j*h/3,k*h/3),physvector< 3  >(0, uy,0),water),begvect[i+k*Nz]);
			begvect[i+k*Nz]->SetConstSpeed(true);
}
}
listvect[j]=begvect;
}
int yloopend=2;


m_list.Calculate0Density();

double t_next=h/3/uy;
while(true){
while(m_list.GetTime()<t_next){
	  double dt;
 m_list.Compute(dt);
  m_list.write(dt);
   }
 
t_next+=h/3/uy;
vector<Particle> & begvect=listvect[yloopend];
for(int i=0;i<Nx;i++){
	
		for(int k=0;k<Nz;k++){
			begvect[i+k*Nz]->SetConstSpeed(false);
			Add(ParticleReal(physvector< 3  >(i*h/3,0,k*h/3),physvector< 3  >(0, uy,0),water),begvect[i+k*Nz]);
			begvect[i+k*Nz]->SetConstSpeed(true);
}
}
--yloopend;
if(yloopend<0){
	yloopend=Ny-1;
}
m_list.Calculate0Density();

 }

}
