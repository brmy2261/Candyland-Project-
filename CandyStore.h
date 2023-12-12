#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Random.h"

using namespace std;

class CandyStore 
{
    private:
        const static int _MAX_CANDIES = 3;
        Candy _candies[_MAX_CANDIES];
        void displayCandies();

    public:
        CandyStore();
        void visitCandyStore(Player&, vector<Candy>);
};

#endif