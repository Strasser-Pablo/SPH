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
int Ny=1;
int Nz=10;
for(int i=0;i<Nx;i++){
	for(int j=0;j<Ny;j++){
		for(int k=0;k<Nz;k++){
	Add(ParticleReal(physvector< 3  >(i*h/3,j*h/3,k*h/3),physvector< 3  >(0, uy,0),water));
}
	}
}



m_list.Calculate0Density();
double t_next=h/3/uy;
 while(true){

while(m_list.GetTime()<t_next){
 m_list.Compute();
  m_list.write();
   }
t_next+=h/3/uy;
for(int i=0;i<Nx;i++){
	for(int j=0;j<Ny;j++){
		for(int k=0;k<Nz;k++){
	Add(ParticleReal(physvector< 3  >(i*h/3,j*h/3,k*h/3),physvector< 3  >(0, uy,0),water));
}
	}
}
m_list.Calculate0Density();
 }

}
