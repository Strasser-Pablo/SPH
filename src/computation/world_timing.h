#ifndef WORLD_TIMING_H
#define WORLD_TIMING_H

#include "world.h"
#include "particles_list.h"
#include <fstream>


/**
* \file world_test.h
*  @brief This file contain Header file for World_test.
*/



using namespace std;
/**
* @brief This class created the position of particle and say when to output. And in witch file.
*
**/
class World_timing_elem:public World {

public:
	/**
	* Default constructor outfile is default
	*/
	World_timing_elem();
	/**
	* Make the calculation.
	*\return void Nothing
	*/
	void Do(int N,fstream & out);
};

class World_timing{

public:
	/**
	* Default constructor outfile is default
	*/
	World_timing();
	/**
	* Make the calculation.
	*\return void Nothing
	*/
	void Do();
};


#endif //WORLD_TIMING_H
