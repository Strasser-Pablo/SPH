#include "particles_deque_list.h"
using namespace std;
Particles_Deque_List::Particles_Deque_List(){

}

Particles* Particles_Deque_List::operator[](size_type index){
	return m_vect[index];
}


const Particles* Particles_Deque_List::operator[](size_type index) const {
	return m_vect[index];
}

deque<Particles*>::iterator Particles_Deque_List::begin(){
	return m_vect.begin();
}
deque<Particles*>::const_iterator Particles_Deque_List::begin() const {
	return m_vect.begin();
}
deque<Particles*>::iterator Particles_Deque_List::end(){
	return m_vect.end();
}
deque<Particles*>::const_iterator Particles_Deque_List::end() const {
	return m_vect.end();
}
void Particles_Deque_List::push_back(const_reference part){
	m_vect.push_back(part);
}
Particles_Deque_List::size_type Particles_Deque_List::size() const {
	return m_vect.size();
}

void Particles_Deque_List::Update(map<Key<DIM>,Particles> & mymap){
	deque<Particles*> vtemp;
	//create a new deque and copy only the necessary particles
	for(deque<Particles*>::iterator it=m_vect.begin(); it!=m_vect.end(); ++it) {
		if(!(*it)->GetMussBeDeleted()) {
			vtemp.push_back(*it);
		}
		else{
			//Particles need to be deleted, we remove neighbour of the particles.
			Voisin v;
			(*it)->GetNeighbour(v);
			list<Particles*> l=v.GetParticlesVect();
			for(list<Particles*>::iterator it2=l.begin(); it2!=l.end(); it2++) {
				(*it2)->RemoveParticlesNeighbour(*it);
			}
			mymap.erase((*it)->GetKey());
		}
	}
	vtemp.swap(m_vect);
}