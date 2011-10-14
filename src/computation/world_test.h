#ifndef WORLD_TEST_H
#define WORLD_TEST_H

#include "world.h"
#include "particles_list.h"
#include <fstream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

/**
* \file world_test.h
*  @brief This file contain Header file for World_test.
*/



using namespace std;
/**
* @brief This class created the position of particle and say when to output. And in witch file.
*
**/
class World_test:public World
{

public:
 /**
 * Default constructor outfile is default
 */
    World_test();
    /**
    * Make the calculation.
    *\return void Nothing
    */
    void Do();
};


#endif //WORLD_TEST_H
