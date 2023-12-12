#include "Random.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int Random::generate(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}