#include <concurrent_vector.h>
using namespace tbb;
class Particles;
class Particles_Deque_List{
	concurrent_vector<Particles*> m_vect;
	int m_n;
public:
	Particles_Deque_List();
	Particles* operator[](size_type index);
	const Particles* operator[](size_type index) const;
	concurrent_vector<Particles*>::iterator begin();
	concurrent_vector<Particles*>::const_iterator begin() const;
	concurrent_vector<Particles*>::iterator end();
	concurrent_vector<Particles*>::const_iterator end() const;
	size_type push_back(Particles* );
}