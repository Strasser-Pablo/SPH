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

 for(int i=0;i<1000000;i++){
Add(ParticleReal(physvector< 3  >(1,i*0.1*i,1),water,2.0,4.0,5.0));
 }
//m_list.Dump();
cout<<"compute"<<endl;
for(int i=0;i<1;i++){
   cout<<i<<endl;
 m_list.Compute(); 
// m_list.Dump();
 cout<<"computed"<<endl;
 ar<<m_list;
 cout<<"written"<<endl;

}
//m_list.Dump();
}
