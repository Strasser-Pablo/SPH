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





int Nx=15;
int Ny=15;
int Nz=15;
for(int i=0;i<Nx;i++){
	for(int j=0;j<Ny;j++){
		for(int k=0;k<Nz;k++){
	Add(ParticleReal(physvector< 3  >(i*h/3,j*h/3,k*h/3),physvector< 3  >(0,3,0),water,1000));
}
	}
}
 m_list.FindBoundary();
m_list.Calculate0Density();

 for(int k=0;k<0;k++){
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
