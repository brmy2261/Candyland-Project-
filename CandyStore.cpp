#include "CandyStore.h"
#include "Random.h"
#include <iostream>

using namespace std;

CandyStore::CandyStore()
{
}

void CandyStore::visitCandyStore(Player &player, vector<Candy> candies)
{
    string candy_choice;
    Random _random;
    Candy candy;
    int random_number;
    bool valid_choice = false;

    for (int i = 0; i < _MAX_CANDIES; i++)
    {
        random_number = _random.generate(0, candies.size() - 1);
        _candies[i] = candies[random_number];
        candies.erase(candies.begin() + random_number);
    }

    displayCandies();
    cout << "please make your selection by typing a valid candy name, or, type 'exit' to exit the candy store: " << endl;

    do
    {
        cin >> candy_choice;
        if (candy_choice == "exit")
        {
            valid_choice = true;
        }
        for (int i = 0; i < _MAX_CANDIES; i++)
        {
            if (_candies[i].name == candy_choice)
            {
                valid_choice = true;
                candy = _candies[i];
                break;
            }
        }
        if (valid_choice == false)
        {
            cout << "please type in a valid candy name or 'exit'!" << endl;
        }
    } while (valid_choice == false);

    if (candy_choice != "exit")
    {
        // make sure player has enough gold to buy a candy
        if (candy.price > player.getGold())
        {
            cout << "you do not have enough gold to purchase this candy!" << endl;
        }
        else if (player.getCandies().size() == 9)
        {
            string swap_choice;
            // ask if they would like to replace an existing candy
            cout << "you do not have sufficient space in your inventory for a new candy, would you like to replace one? (y/n)" << endl;
            valid_choice = false;
            do
            {
                cin >> swap_choice;
                if (swap_choice == "y" || swap_choice == "n")
                {
                    valid_choice = true;
                }

                if (valid_choice == false)
                {
                    cout << "please type in 'y' or 'n'!" << endl;
                }
            } while (valid_choice == false);

            if (swap_choice == "y")
            {
                cout << "which candy would you like to replace?" << endl;

                for (int i = 0; i < player.getCandies().size(); i++)
                {
                    cout << "[" << player.getCandies()[i].name << "] ";
                }
                cout << endl;
                cout << "enter a valid candy name: " << endl;
                valid_choice = false;
                do
                {
                    cin >> swap_choice;
                    for (int i = 0; i < player.getCandies().size(); i++)
                    {
                        if (player.getCandies()[i].name == swap_choice)
                        {
                            valid_choice = true;
                            break;
                        }
                    }
                    if (valid_choice == false)
                    {
                        cout << "please type in a valid candy name!:" << endl;
                    }
                } while (valid_choice == false);
                player.removeCandy(swap_choice);
                player.addCandy(candy);
                player.removeGold(candy.price);
            }
            else
            {
                cout << "suit yourself!" << endl;
            }
        }
        else
        {
            player.addCandy(candy);
            player.removeGold(candy.price);
            cout << "candy " << candy.name << " has been added to your inventory!" << endl;
        }
    }
}

void CandyStore::displayCandies()
{
    cout << ORANGE << "welcome to the candy store: " << RESET << endl;
    cout << "===========================================================" << endl;
    for (int i = 0; i < _MAX_CANDIES; i++)
    {
        cout << "name: " << _candies[i].name << endl;
        cout << "description: " << _candies[i].description << endl;
        cout << "effect: " << _candies[i].effect_type << endl;
        cout << "effect value: " << _candies[i].effect_value << endl;
        cout << "candy type: " << _candies[i].candy_type << endl;
        cout << "price: " << _candies[i].price << endl;
        cout << "===========================================================" << endl;
    }
}