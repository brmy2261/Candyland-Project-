#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <vector>

using namespace std;

struct Card
{
    string color;
    bool isX2;
    string description;
};

struct Candy
{
    string name;
    string description;
    double price;
    string candy_type;
    string effect_type;
    int effect_value;
};

struct Tile
{
    string color;
    string tile_type; // regular, shortcut, ice cream, gumdrop, gingerbread
    bool hidden_treasure;
    bool candy_store;
    bool calamity;
    int gummy; // 0, 1, or 2
};

struct Character
{
    string name;
    int stamina;
    int gold;
    vector<Candy> candies;
};

struct Riddle
{
    string question;
    string answer;
};

#endif