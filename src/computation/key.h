
#ifndef KEY_H
	#define KEY_H
#include "const.h"
#include <list>
	using namespace std;


	/** \file
	 *  @brief Contain the definition of keys used to access particle
	 *
	 *  This file consist of a template Class Key
	 *  Two specialisation exist, one for two dimension and one for three dimension.
	 *  The Key is used for map to access a group of particle (Particles).
	 */

	/**
	 * @brief Base template class
	 *
	 **/
	template<int n=DIM>
	class Key {
	Key(){
	};
	};


	/**
	 * @brief A 2d Key. Used in map to access particle.
	 * Consist of 2 int. With an order.
	 **/
	template<>
	class Key<2>{
	int m_x;
	int m_y;
public:
	/**
	 * @brief Default constructor. Initialize to 0.
	 **/
	inline Key();
	/**
	 * @brief Construct a 2d Key.
	 *
	 * @param x xvalue
	 * @param y yvalue
	 **/
	inline Key(int x,int y);
	/**
	 * @brief Compute the Neighbour of the key. The Neighbour consist of (x+-1, y+-1).
	 *
	 * @return :list< Key< 2 > > List of key
	 **/
	inline list<Key<2> > GetNeighbour() const;

	/**
	 * @brief < operator for key. Test the inegality from x to y. If the first component is the same, test the next.
	 * 
	 * @param A Key to compare with.
	 * 
	 * */
	inline bool operator<(const Key<2> A) const;

	/**
	 * @brief == operator for key. Test equality element by element.
	 **/
	inline bool operator==(const Key<2> A) const;

	/**
	 * @brief Dump value of the key, used for debuging
	 *
	 * @return void
	 **/
	inline void Dump() const;
	/**
	 * @brief Get the x component.
	 *
	 * @return int x component.
	 **/
	inline int GetX() const;
	/**
	 * @brief Get the y component.
	 *
	 * @return int y component.
	 **/
	inline int GetY() const;
	};

	/**
	 * @brief A 3d Key. Used in map to access particle.
	 * Consist of 3 int. With an order.
	 **/
	template<>
	class Key<3>{
	int m_x;
	int m_y;
	int m_z;
public:
	/**
	 * @brief Default constructor make nothing. Initialize to 0.
	 **/
	inline Key();
	/**
	 * @brief Construct a 3d Key
	 *
	 * @param x xvalue
	 * @param y yvalue
	 * @param z zvalue
	 **/
	inline Key(int x,int y,int z);
	/**
	 * @brief Compute the Neighbour of the key. The Neighbour consist of (x+-1, y+-1).
	 *
	 * @return :list< Key< 3 > > List of Key
	 **/
	inline list<Key<3> > GetNeighbour() const;
	/**
	 * @brief < operator for key. Test the inegality from x to z. If the first component is the same, test the next.
	 **/
	inline bool operator<(const Key<3> A) const;
	/**
	 * @brief == operator for key. Test equality element by element.
	 **/
	inline bool operator==(const Key<3> A) const;
	/**
	 * @brief Dump value of the key. Usefull for debuging
	 *
	 * @return void
	 **/
	inline void Dump() const;

	/**
	 * @brief Get the x value.
	 *
	 * @return int x value.
	 **/
	inline int GetX() const;
	/**
	 * @brief Get the y value.
	 *
	 * @return int y value.
	 **/
	inline int GetY() const;
	/**
	 * @brief Get the z value.
	 *
	 * @return int z value.
	 **/
	inline int GetZ() const;
	};



#include "key.htt"

#endif
