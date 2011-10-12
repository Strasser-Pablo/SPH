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

  
  
   
  
  
      for(int x=1;x<5;x++){
 for(int y=1;y<10;y++){
 
Add(ParticleReal(physvector< 3  >(0,x,y),physvector< 3  >(0,0,0),water,10000));
 }
 }
 
     for(int x=5;x<10;x++){
 for(int y=1;y<10;y++){
 
Add(ParticleReal(physvector< 3  >(0,x,y),physvector< 3  >(0,0,0),water,10000));
 }
 }
 
  for(int y=1;y<10;y++){
 
Add(ParticleReal(physvector< 3  >(0,0,y),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,10,y),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,y,0),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,y,10),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,-1,y),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,11,y),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,y,-1),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,y,11),physvector< 3  >(0,0,0),water,10000));
 }
   Add(ParticleReal(physvector< 3  >(0,0,0),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,10,10),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,10,0),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,0,10),physvector< 3  >(0,0,0),water,10000)); 
   Add(ParticleReal(physvector< 3  >(0,-1,-1),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,11,11),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,11,-1),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,-1,11),physvector< 3  >(0,0,0),water,10000)); 
   Add(ParticleReal(physvector< 3  >(0,0,-1),physvector< 3  >(0,0,0),water,10000));
      Add(ParticleReal(physvector< 3  >(0,-1,0),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,11,10),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,10,11),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,10,-1),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,11,0),physvector< 3  >(0,0,0),water,10000));
Add(ParticleReal(physvector< 3  >(0,0,11),physvector< 3  >(0,0,0),water,10000)); 
Add(ParticleReal(physvector< 3  >(0,-1,10),physvector< 3  >(0,0,0),water,10000));   
m_list.Prepare();  
    m_list.write(ar);
 for(int k=0;k<500;k++){
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
