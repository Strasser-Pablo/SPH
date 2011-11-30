#include "world_test.h"
/**
* \file world_test.cpp Implementation file for World_test.
**/


World_test::World_test()
{

}

void World_test::Do()
{
double uy=0.5;
/*
int Nx=10;
int Ny=10;
int Nz=10;

for(int i=0;i<Nx;i++){
	for(int j=0;j<Ny;j++){
		for(int k=0;k<Nz;k++){
			Add(ParticleReal(physvector< 3  >(-(i+0.5)*h/3,j*h/3,k*h/3),physvector< 3  >(0, uy,0),water));
			Add(ParticleReal(physvector< 3  >((i+0.5)*h/3,j*h/3,k*h/3),physvector< 3  >(0, -uy,0),water));
		}
	}
}
m_list.Calculate0Density();

while(true){
	double dt;
 m_list.Compute(dt);
  m_list.write(dt);
   }
*/
 
int Nx=30;
int Ny=3;
int Nz=30;
vector<vector<Particle> > listvect(Ny);
vector<int> yloop(Nx*Nz);
for(int j=0;j<Ny;j++){
	vector<Particle> begvect(Nx*Nz);
for(int i=0;i<Nx;i++){
	
		for(int k=0;k<Nz;k++){
			double x=i*h/3-Nx/2.*h/3+h/12;
			double y=k*h/3-Nz/2.*h/3+h/12;
			double r2=pow(x,2)+pow(y,2);
			if(r2>pow(0.05,2)){
				continue;
			}
			double Uyrel=uy/pow(0.05,2)*(pow(0.05,2)-r2);
			Add(ParticleReal(physvector< 3  >(i*h/3-Nx/2.*h/3+h/6,j*h/3,k*h/3-Nz/2.*h/3+h/6),physvector< 3  >(0, Uyrel,0),water),begvect[i+k*Nz]);
			begvect[i+k*Nz]->SetConstSpeed(true);
			yloop[i+k*Nz]=Ny-1;
}
}
listvect[j]=begvect;
}




m_list.Calculate0Density();


while(true){
	  double dt;
 m_list.Compute(dt);
 m_list.write(dt);


for(int i=0;i<Nx;i++){
	
		for(int k=0;k<Nz;k++){
			vector<Particle> & begvect=listvect[yloop[i+k*Nz]];
			Particle ptemp=begvect[i+k*Nz];
			
			
			double x=i*h/3-Nx/2.*h/3+h/12;
			double z=k*h/3-Nz/2.*h/3+h/12;
			double r2=pow(x,2)+pow(z,2);
			if(r2>pow(0.05,2)){
				continue;
			}
			double y;
			ptemp->GetPos().Get(x,y,z);
			if(y>h){

			double Uyrel=uy/pow(0.05,2)*(pow(0.05,2)-r2);
			int isucces=(yloop[i+k*Nz]+1)%Ny;
			listvect[isucces][i+k*Nz]->GetPos().Get(x,y,z);
			y-=h/3;
			begvect[i+k*Nz]->SetConstSpeed(false);
			Add(ParticleReal(physvector< 3  >(i*h/3-Nx/2.0*h/3+h/12.,y,k*h/3-Nz/2.*h/3+h/12.),physvector< 3  >(0,Uyrel,0),water),begvect[i+k*Nz]);
			begvect[i+k*Nz]->SetConstSpeed(true);
			--yloop[i+k*Nz];
			if(yloop[i+k*Nz]<0){
				yloop[i+k*Nz]=Ny-1;
			}
			}
}
}

 }

}
