#include "world_test.h"

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

  
  
   
  
    for(int x=0;x<4;x++){
      for(int y=0;y<4;y++){
 for(int z=0;z<4;z++){
 
Add(ParticleReal(physvector< 3  >(0.1*x,0.1*y,0.1*z),physvector< 3  >(0,0,0),water,1000.0));
 }
 }
    } 
  
 for(int k=0;k<50;k++){
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
