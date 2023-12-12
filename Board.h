#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Structs.h"
#include "Player.h"
#include "Colors.h"
#include "Deck.h"
#include "Random.h"

using namespace std;

class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    vector<Player> _players;
    const static int _SPECIAL_TILE = 20;
    const static int _TREASURE_TILE = 2;
    void setCandyStores();
    void setSpecialTiles();
    void setHiddenTreasure();
    void displayTile(int);
    Random _random;

public:
    Board();
    void resetBoard();
    void displayBoard(vector<Player>);

    bool movePlayerByCard(int, vector<Player> &, Card);
    bool movePlayerToPosition(int, vector<Player> &, int);

    int getBoardSize() const;

    string getHiddenTreasure();
    string getCalamity();

    Tile getTile(int);

    void setGummyTile(int, int);
};

#endif