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






      for(int x=0;x<10;x++){
 for(int y=0;y<10;y++){

Add(ParticleReal(physvector< 3  >(0,x+20,y),physvector< 3  >(0,0,0),water,0.5,1000));
 }
 }


   for(int x=0;x<10;x++){
 for(int y=0;y<10;y++){

Add(ParticleReal(physvector< 3  >(0,x,y),physvector< 3  >(0,10,0),water,0.5,10000));
 }
 }


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
