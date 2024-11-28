/************************************************************************/
/* Blender.hpp                                                          */
/* To defined behaviour of our bot										*/
/* To introduce our states of our bot								    */
/************************************************************************/
#include "Map.hpp"

#include <vector>

class Blender {
	
	int state_bot = 0;
	int state_beer_bot = 0;
	int state_invert = 0;
	std::vector< std::pair <int, int >> semaphore_direction = std::vector<std::pair<int, int >>() ;
	int explore = 0; // it indicates the direction/cap of our bot: initially we are on South direction

public:
	
	Map map_to_explore;
	std::pair < int, int > current_position_in_map;

	/**********************/
	/* State of bot       */
	/**********************/
	 
	bool islost;
	 
	bool isalive;

	Blender(std::pair < int, int > start , Map map_to_explore);
	~Blender();

	/************************************************************************/
	/* Functions to define movment of bot and to interogate his state       */
	/************************************************************************/
	void Move_and_Update_State();
	bool CheckLost(int x, int y);
	bool IsAlive();
	bool IsLost();

};
