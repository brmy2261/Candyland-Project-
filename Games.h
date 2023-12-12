#ifndef GAMES_H
#define GAMES_H

#include <iostream>
#include <vector>
#include "Structs.h"

class Games
{
    private:
        vector<Riddle> _riddles; 
        void loadRiddles(string);
        
    public:
        Games();
        bool playRockPaperScissors();
        bool playRiddles();
};

#endif