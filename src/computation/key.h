
#ifndef KEY_H
#define KEY_H
#include "const.h"
#include <list>
using namespace std;


/** \file key.h Contain the definition of keys used to access particle
 *
 */

/**
 * @brief Base template class
 *
 **/
template<int n=DIM>
class Key{
  Key(){};
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
   * @brief Construct a 2d Key
   *
   * @param x xvalue
   * @param y yvalue
   **/
  inline  Key(int x,int y);
  /**
   * @brief Compute the Neighbour of the key (x+-1, y+-1)
   *
   * @return :list< Key< 2 > > List of key
   **/
  inline list<Key<2> > GetNeighbour() const;

 /**
   * @brief < operator for key. Test the inegality from x to y. If the first component is the same, test the next.
   **/
  inline bool operator<(const Key<2> A) const;

  /**
   * @brief Dump value of the key, used for debuging
   *
   * @return void
   **/
  inline void Dump() const;
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
     * @brief Construct a 3d Key
     *
     * @param x xvalue
     * @param y yvalue
     * @param z zvalue
     **/
    inline  Key(int x,int y,int z);
    /**
     * @brief Compute the Neighbour of the key (x+-1, y+-1,z+-1)
     *
     * @return :list< Key< 3 > > List of Key
     **/
inline list<Key<3> > GetNeighbour() const;
  /**
   * @brief < operator for key. Test the inegality from x to z. If the first component is the same, test the next.
   **/
inline bool operator<(const Key<3> A) const;

/**
 * @brief Dump value of the key. Usefull for debuging
 *
 * @return void
 **/
inline void Dump() const;
};



#include "key.htt"

#endif
