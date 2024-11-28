/************************************************************************/
/* Map.cpp                                                              */
/* In this file Main class is implemented with behaviour of our bot     */
/*   We also introduce an function for unit test to generate random map */
/************************************************************************/
#include "Map.hpp"



Map::Map() {
	size = 0;
	Sx_start = 0;
	Sy_start = 0;
};


Map::~Map() {

};

/************************************************************************/
/* To display map													    */
/************************************************************************/
void Map::Display_Map() {
	//Starting = 1, Ending, Obstacle, Invert, Beer , Loop, ObstacleN, S, E, N, W, Teleporteur 
	for (int i=0; i < size; i++) {
		for (int j=0; j < size; j++) {
			switch (map.at(i).at(j)) {
			case 0:
				std::cout <<  "0";
				break;
			case 1 :
				std::cout <<  "@";
				break;
			
			case 2:
				std::cout <<  "$";
				break;
			
			case 3:
				std::cout <<  "X";
				break;
			
			case 4:
				std::cout << "I";
				break;
			
			case 5:
				std::cout <<  "B";
				break;
						
			case 7:
				std::cout <<  "#";
				break;
			
			case 8:
				std::cout <<  "S";
				break;
			
			case 9:
				std::cout  << "E";
				break;
			
			case 10:
				std::cout  << "N";
				break;
			
			case 11:
				std::cout  << "O";
				break;

			case 12:
				std::cout  << "T";
				break;
			
		}

			
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	
	
}

/************************************************************************/
/* To display map													    */
/************************************************************************/
void Map::Display_Path() {
	
	std::cout << "Path :\n";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << map_previously_explored.at(i).at(j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}


/***************************************************************************************************/
/* Generate a random cpp                                                                           */
/*  we must check than a map is correctly constructed by assuring than a starting point is present */
/***************************************************************************************************/
void Map::Generate_Map() {
	int x = 10;
	while (false) {
		std::cout << " Could you lease enter size of grid ? (Number must be between 0 and 100 ) ";
		std::cin >> x; // Get user input from the keyboard
		std::cout << "Your number is: " << x;

		if (x > 100) {
			std::cout << " Please enter a value between 0 and 100 \n";
		}
		else {
			break;
		}
	}
	size = x;


	/************************************************************************/
	/* Init map with 0 value											    */
	/************************************************************************/
	for (int i = 0; i < size; i++) {
		std::vector<int> vect(x, 0);
		map.push_back(vect);
	}
	/************************************************************************/
	/* Init Map already explored with 0 value							    */
	/************************************************************************/
	for (int i = 0; i < size; i++) {
		std::vector<int> vect(x, 0);
		map_previously_explored.push_back(vect);
	}

	/************************************************************************/
	/* we use std, for reason of compatibility with your endvironment :     */
	/* even if opencv is more adpated to process matrix object or cv::Mat   */
	/************************************************************************/
	
	//randomize position of starting : global attribute is set ( for starting position )
	std::cout << "random start :\n";
	Sx_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));;
	Sy_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));;
	map.at(Sx_start).at(Sy_start) = Starting;

	//randomize suicide point
	
	int S2x_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));;
	int S2y_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));;
	if ( map.at(S2x_start).at(S2y_start) != Starting) { map.at(S2x_start).at(S2y_start) = Ending; } // to assure Map correctly constructed

	//randomize beer in map
	
	for (int i = 0; i < ((int)(((double)std::rand() / RAND_MAX) * (size)));  i++) {
		int Ox_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		int Oy_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		if (map.at(Ox_start).at(Oy_start) != Starting) { map.at(Ox_start).at(Oy_start) = Beer; }
		//map.at(Ox_start).at(Oy_start) = Beer;
	}

	//randomize obstacle in map
	
	for (int i = 0; i < ((int)(((double)std::rand() / RAND_MAX) * (size))); i++) {
		int Ox_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		int Oy_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		if (map.at(Ox_start).at(Oy_start) != Starting) { map.at(Ox_start).at(Oy_start) = Obstacle; }
		
	}

	//randomize obstacle in map
	
	for (int i = 0; i < ((int)(((double)std::rand() / RAND_MAX) * (size))); i++) {
		int Ox_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		int Oy_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		if (map.at(Ox_start).at(Oy_start) != Starting) { map.at(Ox_start).at(Oy_start) = ObstacleN; }
		
	}
	
	
	//randomize invert command
	for (int i = 0; i < 1 + ((int)(((double)std::rand() / RAND_MAX) * (size))); i++) {
		int Ix_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		int Iy_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		
		if (map.at(Ix_start).at(Iy_start) != Starting) { map.at(Ix_start).at(Iy_start) = Invert;}
	}

	
	//randomize invert command
	for (int i = 0; i < 1 + ((int)(((double)std::rand() / RAND_MAX) * (size))); i++) {
		int Ix_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		int Iy_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		if (map.at(Ix_start).at(Iy_start) != Starting) { map.at(Ix_start).at(Iy_start) = S; }
		
	}

	
	//randomize invert command
	for (int i = 0; i < 1 + ((int) ((((double)std::rand() / RAND_MAX) * (size)))); i++) {
		int Ix_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		int Iy_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		if (map.at(Ix_start).at(Iy_start) != Starting) { map.at(Ix_start).at(Iy_start) = E; }
		
	}

	
	//randomize invert command
	for (int i = 0; i < 1 + ((((double)std::rand() / RAND_MAX) * (size))); i++) {
		int Ix_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		int Iy_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		
		if (map.at(Ix_start).at(Iy_start) != Starting) { map.at(Ix_start).at(Iy_start) = N; }
	}

	
	//randomize invert command
	for (int i = 0; i < 1 + ((((double)std::rand() / RAND_MAX) * (size-1))); i++) {
		int Ix_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		int Iy_start = ((int)(((double)std::rand() / RAND_MAX) * (size)));
		if (map.at(Ix_start).at(Iy_start) != Starting) { map.at(Ix_start).at(Iy_start) = W; }
		
	}

	
	//randomize teleporteur : only once
	
	int Ox_start_T = ((int)(((double)std::rand() / RAND_MAX) * (size)));
	int Oy_start_T = ((int)(((double)std::rand() / RAND_MAX) * (size)));
	map.at(Ox_start_T).at(Oy_start_T) = Teleporteur;

	int Ox_start2_T = ((int)(((double)std::rand() / RAND_MAX) * (size)));
	int Oy_start2_T = ((int)(((double)std::rand() / RAND_MAX) * (size)));
	map.at(Ox_start2_T).at(Oy_start2_T) = Teleporteur;
		
	std::pair<int, int> first = std::pair<int, int>(Ox_start_T, Oy_start_T);
	std::pair<int, int> second = std::pair<int, int>(Ox_start2_T, Oy_start2_T);
	teleporteur.push_back(first);
	teleporteur.push_back(second);
	

};