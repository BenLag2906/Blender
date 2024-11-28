/************************************************************************/
/* Map.hpp		                                                        */
/* To modelize the game with rule : obstacle,...						*/
/* To define a genration of map game for integration test to check 	    */
/************************************************************************/
#include <vector>
#include <iostream>
/************************************************************************/
/* Enum to different state of map                                       */
/*  - Starting : starting point                                         */
/*  - Ending   : suicide point for our bot                              */
/*  - .....                                                             */
/************************************************************************/
enum Suit { Starting = 1, Ending, Obstacle, Invert, Beer , Loop, ObstacleN, S, E, N, W, Teleporteur };

class Map {
	public:
		std::vector<std::vector<int>> map;
		std::vector<std::vector<int>> map_previously_explored;
		std::vector<std::pair<int,int> > teleporteur;
		int size;
		int Sx_start;
		int Sy_start;
		Map();
		~Map();
		void Generate_Map();
		void Display_Map();
		void Display_Path();
};