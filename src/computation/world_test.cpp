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
int Ny=1;
int Nz=10;
for(int i=0;i<Nx;i++){
	for(int j=0;j<Ny;j++){
		for(int k=0;k<Nz;k++){
	Add(ParticleReal(physvector< 3  >(i*h/3,j*h/3,k*h/3),physvector< 3  >(0,1,0),water));
}
	}
}


m_list.Calculate0Density();

 while(true){

//m_list.Dump();
for(int i=0;i<9;i++){
 m_list.Compute(ar);
  m_list.write();
}

// m_list.Dump();
	for(int x=0;x<Nx;x++){
	for(int y=0;y<Ny;y++){
		for(int z=0;z<Nz;z++){
	Add(ParticleReal(physvector< 3  >(x*h/3,y*h/3,z*h/3),physvector< 3  >(0,1,0),water));
}
	}
}
m_list.Calculate0Density();
cout<<"part added"<<endl;
 m_list.write();

   }





bool bfalse=false;
ar<<BOOST_SERIALIZATION_NVP(bfalse);
//m_list.Dump();
}
