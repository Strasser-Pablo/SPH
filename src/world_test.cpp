#include "world_test.h"

World_test::World_test()
{

}

void World_test::Do()
{
 ;
 // a.Dump();
Add(ParticleReal(physvector< 3  >(1,1,1),water,2.0,4.0,5.0));
//m_list.Dump();
cout<<"compute"<<endl;
for(int i=0;i<100;i++){
 m_list.Compute(); 
// m_list.Dump();
}
m_list.Dump();
}
