#include "world_test.h"
/**
* \file world_test.cpp Implementation file for World_test.
**/


World_test::World_test()
{

}

void World_test::Do()
{
 ;
 // a.Dump();
  ofstream out("default");
  boost::archive::binary_oarchive ar(out);
//boost::archive::xml_oarchive ar(out);





int Nx=10;
int Ny=10;
for(int i=0;i<Nx+1;i++){
	Add(ParticleReal(physvector< 3  >(i*h/3,0,0),physvector< 3  >(0,0,0),water,1000,false,true));
}
  
for(int j=1;j<Ny;j++){
	Add(ParticleReal(physvector< 3  >(0,j*h/3,0),physvector< 3  >(0,0,0),water,1000,false,true));
	for(int i=1;i<Nx;i++){
	Add(ParticleReal(physvector< 3  >(i*h/3,j*h/3,0),physvector< 3  >(0,0,0),water,1000));
	}
	Add(ParticleReal(physvector< 3  >(h/3*Nx,j*h/3,0),physvector< 3  >(0,0,0),water,1000,false,true));
	}
	
	for(int i=0;i<Nx+1;i++){
	Add(ParticleReal(physvector< 3  >(i*h/3,Ny*h/3,0),physvector< 3  >(0,0,0),water,1000,false,true));
}
m_list.Calculate0Density();

 for(int k=0;k<200;k++){
  cout<<"k "<<k<<endl;


//m_list.Dump();

 m_list.Compute();
// m_list.Dump();

cout<<"write"<<endl;
 m_list.write(ar);

   }





bool bfalse=false;
ar<<BOOST_SERIALIZATION_NVP(bfalse);
//m_list.Dump();
}
