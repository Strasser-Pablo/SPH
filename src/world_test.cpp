#include "world_test.h"

World_test::World_test()
{

}

void World_test::Do()
{
 ;
 // a.Dump();
 for(int i=0;i<1000;i++){
Add(ParticleReal(physvector< 3  >(1,i*0.1*i,1),water,2.0,4.0,5.0));
 }
//m_list.Dump();
cout<<"compute"<<endl;
for(int i=0;i<10;i++){
 m_list.Compute(); 
// m_list.Dump();
 cout<<i<<endl;
}
//m_list.Dump();
}
