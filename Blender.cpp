/************************************************************************/
/* Blender.cpp                                                          */
/* In this file Main class is implemented with behaviour of our bot     */
/* We also introduce an function for unit test to generate random map   */
/************************************************************************/

#include <iostream>
#include <vector>
#include "Blender.hpp"




/************************************************************************/
/*  Constructor of bot                                                 */
/************************************************************************/
Blender::Blender(std::pair < int, int > start, Map map) {

    //Init private objected
    state_beer_bot = 0;                   //He have no drunk ( at the beginning )
    state_invert = 0;
    
    state_bot = 0;
    explore = 0;
    semaphore_direction = std::vector<std::pair<int, int >>();
    semaphore_direction.push_back(std::pair<int, int >(1 , 0) ); //one is for South direction
    semaphore_direction.push_back(std::pair<int, int >(0 , 1) ); //one is for East direction
    semaphore_direction.push_back(std::pair<int, int >(-1, 0) ); //one is for North direction
    semaphore_direction.push_back(std::pair<int, int >(0, -1) ); //one is for West direction


    map_to_explore = map;
    current_position_in_map = start;

    islost = false;
    isalive = true;

    map_to_explore.map_previously_explored.at(current_position_in_map.first).at(current_position_in_map.second) = 1;
    
};

/*****************************************************************************************************/
/*  Destructor of bot ( even if bot is dead !) memory leak could happen, in more complex object      */
/*****************************************************************************************************/
Blender::~Blender() {

};

/*************************************/
/*  Check functions of our bot       */
/*  return : bool                    */ 
/*************************************/
bool Blender::IsAlive() {
    return !(state_bot == Ending);
};

/*************************************/
/*  Check functions of our bot       */
/*  return : bool                    */
/*************************************/
bool Blender::IsLost() {
    return (state_bot == Loop);
};

/*************************************/
/*  Check if our bot is lost        */
/*  return : bool                    */
/*************************************/
bool Blender::CheckLost(int x_test, int y_test) {
    
    return ( map_to_explore.map_previously_explored.at(x_test).at(y_test) == 1 );
};

/*************************************/
/*  move fucntion of our bot         */
/*************************************/
void Blender::Move_and_Update_State() {

    //Bot is current_position_in_map;
    // We estimate potential move
    //    With semaphore_direction and his state of inversion before

    int x = current_position_in_map.first;
    int y = current_position_in_map.second;

    //To avoid blocked bot in a starting or after a teleportation : regression case
    int previous_x = x;
    int previous_y = y;

    int sens = 1;
    

    if (state_invert == 0) {
        //semaphore_direction are in normal order
        
        sens = 1;
    }
    else {
        //semaphore_direction are in inverse order
        
        sens = -1;

    }

    

    /**************************************************************/
    /*  We start exploration                                      */
    /**************************************************************/
    int cycle = 0; //to avoid to change directionnality after one loop on possible direction
        
    while ((explore < 4) && (explore > -1) && ( cycle < 4) ) {

        //We apply the rule with our deplacement gradient indicated by semaphore
        int candidate_x = x + semaphore_direction.at(explore).first;
        int candidate_y = y + semaphore_direction.at(explore).second;

        //we must check his position now
       
        if (((candidate_x > (map_to_explore.size-1)) || (candidate_x < 0)) || ((candidate_y > (map_to_explore.size-1)) || (candidate_y < 0))) {
            /**************************************************************/
            /* Candidate movement is not valid                            */
            /* ( Next iteration to explore )                              */
            /* considerred in code as an obstacle                         */
            /**************************************************************/
            
            explore = explore + sens;
            cycle++;

            /*****************************************************************/
            /* we must loop on or list of direction for the next exploration */ 
            /* for this case we have reah limit of size of vector direction  */
            /*****************************************************************/
            if (explore > 3) { explore = 0; }
            if (explore < 0) { explore = 3; }
            
            continue;

        }

        if ((map_to_explore.map.at(candidate_x).at(candidate_y) == Obstacle) && (state_beer_bot > 0)) {
            //We destroy the obstacle ( rule of the game )
            map_to_explore.map.at(candidate_x).at(candidate_y) = 0;

            //we consider our energy in a beer has been used
            state_beer_bot--;
           
        }
        else {
            if ( (map_to_explore.map.at(candidate_x).at(candidate_y) == Obstacle) )  {
                /***************************************************/
                /* Candidate movement is not possible              */
                /* We need to find beer ! and change direction     */
                /***************************************************/
               
                explore = explore + sens;
                if (explore > 3) { explore = 0; }
                if (explore < 0) { explore = 3; }
                cycle++;
                continue;
            }
            
        }


        if ((map_to_explore.map.at(candidate_x).at(candidate_y) == ObstacleN)) {
            explore = explore + sens; //need to process new exploration
            cycle++;

            /*****************************************************************/
            /* we must loop on or list of direction for the next exploration */
            /* for this case we have reah limit of size of vector direction  */
            /*****************************************************************/
            if (explore > 3) { explore = 0; }
            if (explore < 0) { explore = 3; }
            continue;
        }
           
        /**************************************************************************************************/
        /* At this step the move is possible                                                              */
        /* We can break the exploration and update our state with this new position                        */
        /**************************************************************************************************/
        switch (explore) {
            case 0:
                std::cout << "South\n";
            break;
            case 1:
                std::cout << "East\n";
                break;
            case 2:
                std::cout << "North\n";
                break;
            case 3:
                std::cout << "West\n";
                break;
        }
        current_position_in_map.first = candidate_x;
        current_position_in_map.second = candidate_y;
        
        if(CheckLost(candidate_x, candidate_y)) {
            
            std::cout << "Loop\n";
            state_bot = Loop;
        }
        map_to_explore.map_previously_explored.at(candidate_x).at(candidate_y) = 1;
        x = candidate_x;
        y = candidate_y;
        break;
    }


    if ((x == previous_x) && (y == previous_y)) {

        //To avoid :
        
        
        // 0X0TX00000
        // 000#@XI000

        //In regression: a genrrate case must be added
        state_bot = Loop;
        return;
    }

    /************************************************************/
    /* if this position is indicate by T                        */
    /*    We automatically link to the other side               */
    /* notice than we only manage one instance of this object() */
    /************************************************************/
    if (map_to_explore.map.at(x).at(y) == Teleporteur) {
        
        std::pair<int, int> first = map_to_explore.teleporteur.at(0);
        std::pair<int, int> second = map_to_explore.teleporteur.at(1);

        if ((first.first == x) && (first.second == y)) {

            current_position_in_map.first = second.first;
            current_position_in_map.second = second.second;
            map_to_explore.map_previously_explored.at(second.first).at(second.second) = 1;
        }

        if ((second.first == x) && (second.second == y)) {

            current_position_in_map.first = first.first;
            current_position_in_map.second = first.second;
            map_to_explore.map_previously_explored.at(first.first).at(first.second) = 1;
        }

        /*******************************/
        /* Update of position          */
        /*******************************/
        

    }

    /***************************/
    /* Update states of bot    */
    /***************************/
    if (map_to_explore.map.at(x).at(y) == S) {
        //bot direction is update for next move
        explore = 0;
    }
    
    if (map_to_explore.map.at(x).at(y) == E) {
        //bot direction is update for next move
        explore = 1;
    }
    if (map_to_explore.map.at(x).at(y) == N) {
        //bot direction is update for next move
        explore =2 ;
    }
    if (map_to_explore.map.at(x).at(y) == W) {
        //bot direction is update for next move
        explore =3;
    }
    /***************/
    /* Beer   case */
    /***************/
    if (map_to_explore.map.at(x).at(y) == Beer) {
        state_beer_bot++;
    }
    /***************/
    /* invert case */
    /***************/
    if ((map_to_explore.map.at(x).at(y) == Invert)) {
        state_invert = (1 - state_invert);
    }
    /****************/
    /* Suicide case */
    /****************/
    if ((map_to_explore.map.at(x).at(y) == Ending)) {
        state_bot = Ending;
    }


    
};

/************************************************************************/
/* Input of our code                                                    */
/************************************************************************/
int main()
{
    std::cout << "Hello blender\n";
    int i = 0;
    while (i < 1000) {
        i++;
        Map* whereisdora = new Map();

        try {
            std::cout << "Map " << i << "\n";
            whereisdora->Generate_Map();
            std::cout << "************\n";
            
        }
        catch (...) {
            std::cout << "generation map\n";
        }

        try {
            whereisdora->Display_Map();
        
        }
        catch (...) {
            std::cout << "display map error\n";
        }
        /******************************************************************/
        /* Link Map created to a new Bot : we give to the bot instruction */
        /******************************************************************/
        Blender* ourbot = new Blender(std::pair<int, int >(whereisdora->Sx_start, whereisdora->Sy_start), *whereisdora);

        try {
            


            while ((ourbot->IsAlive())) {

                if (ourbot->IsLost()) {
                    break;
                }
                ourbot->Move_and_Update_State();



            }
        }
        catch (...) {
            std::cout << "--error--\n" << i ;
            whereisdora->Display_Map();
        }

        try {
            std::cout << "----display-------\n";
            ourbot->map_to_explore.Display_Path();
        }
        catch (...) {
            std::cout << "--errorin display--\n" << i;
            whereisdora->Display_Map();
        }
        std::cout << "************\n";

        /******************************************************************************/
        /*    End of processing. we can display Path of bot ( his life finnally)      */
        /******************************************************************************/


        /*************************/
        /*    Flush objects      */
        /*************************/
        delete ourbot;
        ourbot = NULL;

        delete whereisdora;
        whereisdora = NULL;
    }
}

/************************************************************************/
/* We also introduce a function for unit test to generate random map    */
/************************************************************************/
void functional_test() {
        std::cout << "Run functional Test\n";
    

        std::cout << "Hello blender\n";
        int i = 0;
        while (i < 10) {
            try {
                i++;
                Map* whereisdora = new Map();
                whereisdora->Generate_Map();
                std::cout << "------------\n";
                whereisdora->Display_Map();
                std::cout << "************\n";
                /******************************************************************/
                /* Link Map created to a new Bot : we give to the bot instruction */
                /******************************************************************/
                Blender* ourbot = new Blender(std::pair<int, int >(whereisdora->Sx_start, whereisdora->Sy_start), *whereisdora);


                while ((ourbot->IsAlive())) {

                    if (ourbot->IsLost()) {
                        break;
                    }
                    ourbot->Move_and_Update_State();



                }
                ourbot->map_to_explore.Display_Map();

                /******************************************************************************/
                /*    End of processing. we can display Path of bot ( his life finnally)      */
                /******************************************************************************/


                /*************************/
                /*    Flush objects      */
                /*************************/
                delete ourbot;
                ourbot = NULL;

                delete whereisdora;
                whereisdora = NULL;
            }
                  
            catch (...) {
                std::cout << "Error in Global excution\n";
                //We dump map which has provocated an error to be analyzed
            }


        }

   

}

void unit_test() {
    std::cout << "Run functional Test\n";


    std::cout << "Hello blender\n";
    int i = 0;
    while (i < 10) {
        try {
            i++;
            Map* whereisdora = new Map();
            whereisdora->Generate_Map();
            std::cout << "------------\n";
            whereisdora->Display_Map();
            std::cout << "************\n";
            /******************************************************************/
            /* Link Map created to a new Bot : we give to the bot instruction */
            /******************************************************************/
    
        }
        catch (...) {
            std::cout << "Error in unit test generation of Map\n";
            //We dump map which has provocated an error to be analyzed
        }


    }



}

