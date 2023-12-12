#include "Board.h"
#include "Player.h"
#include "Random.h"
#include "Games.h"
#include "CandyStore.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

vector<Character> loadCharacters(string filename, vector<Candy> candies)
{
    vector<Character> characters;
    ifstream file(filename);
    string candy_name;

    if (file.is_open())
    {
        string line;
        bool is_header = true;
        while (getline(file, line))
        {
            if (is_header == true)
            {
                is_header = false;
            }
            else
            {
                size_t pos = line.find('|');
                if (pos != string::npos)
                {
                    Character character;
                    character.name = line.substr(0, pos);
                    line = line.substr(pos + 1);
                    pos = line.find('|');
                    if (pos != string::npos)
                    {
                        character.stamina = stoi(line.substr(0, pos));
                        line = line.substr(pos + 1);
                        pos = line.find('|');
                        if (pos != string::npos)
                        {
                            character.gold = stoi(line.substr(0, pos));
                            line = line.substr(pos + 1);

                            size_t pos = 0;
                            while ((pos = line.find(',')) != string::npos)
                            {
                                candy_name = line.substr(0, pos);
                                for (int i = 0; i < candies.size(); i++)
                                {
                                    if (candies[i].name == candy_name)
                                    {
                                        character.candies.push_back(candies[i]);
                                        break;
                                    }
                                }
                                line.erase(0, pos + 1);
                            }
                            candy_name = line;
                            for (int i = 0; i < candies.size(); i++)
                            {
                                if (candies[i].name == candy_name)
                                {
                                    character.candies.push_back(candies[i]);
                                    break;
                                }
                            }
                            characters.push_back(character);
                        }
                    }
                }
            }
        }
        file.close();
    }
    else
    {
        cout << "unable to open file: " << filename << endl;
    }

    return characters;
}

vector<Candy> loadCandies(string filename)
{
    vector<Candy> candies;
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        bool is_header = true;
        while (getline(file, line))
        {
            if (is_header == true)
            {
                is_header = false;
            }
            else
            {
                size_t pos = 0;
                string token;
                vector<string> tokens;
                while ((pos = line.find('|')) != string::npos)
                {
                    token = line.substr(0, pos);
                    tokens.push_back(token);
                    line.erase(0, pos + 1);
                }
                token = line;
                tokens.push_back(token);
                Candy candy;
                candy.name = tokens[0];
                candy.description = tokens[1];
                candy.effect_type = tokens[2];
                candy.effect_value = stoi(tokens[3]);
                candy.candy_type = tokens[4];
                candy.price = stod(tokens[5]);
                candies.push_back(candy);
            }
        }
        file.close();
    }
    else
    {
        cout << "unable to open file: " << filename << endl;
    }

    return candies;
}

// get the number of players
// make sure it is more than 1 and less than 5

int getNumberOfPlayers()
{
    string number_of_players;

    // check that number_of_players is more than 0 and less than 5, we can use a do while loop for this
    bool valid_choice = false;
    do
    {
        cout << "enter the number of players: " << endl;
        cin >> number_of_players;
        if (number_of_players == "2" || number_of_players == "3" || number_of_players == "4")
        {
            valid_choice = true;
        }
        else
        {
            cout << "number of players must be between 2 and 4" << endl;
        }

    } while (valid_choice == false);

    return stoi(number_of_players);
}

/*
    1. get the player's name
    2. get the player's character
*/
Player getPlayerInfo(int player_number, vector<Character> characters)
{
    Player player;
    string name;
    string character_name;
    bool character_found = false;

    // get the player's name
    cout << "enter player " << player_number << "'s name: " << endl;
    cin >> name;
    player.setPlayerName(name);

    // show list of available characters
    cout << ORANGE << "welcome to the character selection menu:" << RESET << endl;
    cout << "===========================================================" << endl;
    for (int i = 0; i < characters.size(); i++)
    {
        cout << "character name: " << characters[i].name << endl;
        cout << "character gold: " << characters[i].gold << endl;
        cout << "character stamina: " << characters[i].stamina << endl;
        cout << "candies: ";
        for (int j = 0; j < characters[i].candies.size(); j++)
        {
            cout << "[" << characters[i].candies[j].name << "] ";
        }
        cout << endl;
        cout << "===========================================================" << endl;
    }

    // get the player's character choice by name, make sure it is an actual character
    do
    {
        cout << "please make your selection by typing a valid character name: " << endl;
        cin >> character_name;
        for (int i = 0; i < characters.size(); i++)
        {
            if (character_name == characters[i].name)
            {
                player.setCharacterName(characters[i].name);
                player.setStamina(characters[i].stamina);
                player.setGold(characters[i].gold);
                player.setCandies(characters[i].candies);

                character_found = true;
                break;
            }
        }
    } while (character_found == false);

    return player;
}

int getNextPlayerIndex(int currentIndex, int playerCount)
{
    currentIndex++;
    if (currentIndex > playerCount)
    {
        currentIndex = 0;
    }
    return currentIndex;
}

int getPlayerMenuChoice()
{
    string menu_choice;
    // show menu to player 1. Draw, 2. Candy Store, 3. Stats
    cout << ORANGE << "welcome to the main menu: " << RESET << endl;
    cout << "===========================================================" << endl;
    cout << "1. draw a card" << endl;
    cout << "2. use candy" << endl;
    cout << "3. show player stats" << endl;
    cout << "===========================================================" << endl;
    cout << "please make your selection by typing 1, 2, or 3: " << endl;
    bool valid_choice = false;
    do
    {
        cin >> menu_choice;
        if (menu_choice == "1" || menu_choice == "2" || menu_choice == "3")
        {
            valid_choice = true;
        }
        else
        {
            cout << "please enter 1, 2, or 3!" << endl;
        }
    } while (valid_choice == false);

    return stoi(menu_choice);
}

Candy getPlayerCandyChoice(Player player, vector<Candy> candies, string filterCandyType)
{
    Candy candy;
    string candy_choice;
    bool valid_choice = false;
    cout << "here is your list of candies: " << endl;
    for (int i = 0; i < player.getCandies().size(); i++)
    {
        if (filterCandyType != "" && player.getCandies()[i].candy_type == filterCandyType)
        {
            cout << "[" << player.getCandies()[i].name << "] ";
        }
        if (filterCandyType == "")
        {
            cout << "[" << player.getCandies()[i].name << "] ";
        }
    }
    cout << endl;
    cout << "please type a valid candy name to use, or, type 'exit' to exit: " << endl;

    do
    {
        cin >> candy_choice;
        if (candy_choice == "exit")
        {
            valid_choice = true;
        }
        for (int i = 0; i < player.getCandies().size(); i++)
        {
            if (player.getCandies()[i].name == candy_choice)
            {
                valid_choice = true;
                break;
            }
        }
        if (valid_choice == false)
        {
            cout << "please type in a valid candy name!" << endl;
        }
    } while (valid_choice == false);

    if (candy_choice != "exit")
    {
        for (int i = 0; i < candies.size(); i++)
        {
            if (candies[i].name == candy_choice)
            {
                candy = candies[i];
                break;
            }
        }
    }
    return candy;
}

bool checkForHailStorm()
{
    Random random;
    int random_number = random.generate(1, 100);
    if (random_number <= 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    Board board;
    vector<Player> players;
    Deck deck;
    Card card;
    Tile tile;
    CandyStore candy_store;
    Random random;
    Games games;
    Candy candy;
    bool winner = false;
    int player_index = 0;
    bool next_player = false;

    string characters_file = "Characters.txt";
    string candies_file = "Candies.txt";

    vector<Candy> candies = loadCandies(candies_file);
    vector<Character> characters = loadCharacters(characters_file, candies);

    // get the number of players between 2 and 4
    int number_of_players = getNumberOfPlayers();
    number_of_players--;

    // get each player's info
    for (int i = 0; i <= number_of_players; i++)
    {
        // get player name
        // get player character choice
        Player player = getPlayerInfo(i + 1, characters);

        // remove character
        for (int j = 0; j < characters.size(); j++)
        {
            if (player.getCharacterName() == characters[j].name)
            {
                characters.erase(characters.begin() + j);
                break;
            }
        }
        players.push_back(player);
    }

    // let each player visit the candy store
    for (int i = 0; i < players.size(); i++)
    {
        cout << "it is " << players[i].getPlayerName() << "'s turn to visit the candy store!" << endl;
        candy_store.visitCandyStore(players[i], candies);
    }

    // main loop
    do
    {
        next_player = false;

        cout << "the current player is: " << players[player_index].getPlayerName() << endl;

        if (players[player_index].getMissedTurns() > 0)
        {
            // player missed a turn, so decrement their missed turns by 1
            players[player_index].removeMissedTurns(1);

            cout << RED << "player missed turn!" << RESET << endl;

            next_player = true;
        }
        else if (players[player_index].getStamina() == 0 && players[player_index].getMissedTurns() == 0)
        {
            // if a player's stamina drops to 0, they miss 2 turns
            cout << RED << "sorry " << players[player_index].getPlayerName() << ", but your stamina has dropped to 0 and you will miss 2 turns." << RESET << endl;
            // give them an opportunity to use one of their stamina boosting candies so they don't miss more than 2 turns.
            cout << "here is a chance to use a magical candy to add stamina, so that you don't lose 2 more turns!" << endl;
            candy = getPlayerCandyChoice(players[player_index], candies, "magical");
            if (candy.name != "" && candy.candy_type == "stamina")
            {
                players[player_index].addStamina(candy.effect_value);
                cout << "you have added " << candy.effect_value << " stamina." << endl;
            }
            next_player = true;
        }
        else
        {
            // get the player menu choice (display the menu first)
            int player_menu_choice = getPlayerMenuChoice();
            switch (player_menu_choice)
            {
            case 1: // draw a card
                card = deck.drawCard();
                cout << "your card is ";
                deck.printCard();
                cout << endl;

                // move the player using the card
                winner = board.movePlayerByCard(player_index, players, card);

                if (winner == true)
                {
                    cout << "we have a winner! congratulations " << players[player_index].getPlayerName() << "!" << endl;
                }
                else
                {
                    tile = board.getTile(players[player_index].getBoardPosition());

                    if (tile.tile_type == "regular")
                    {
                        // candy store
                        // hidden treasure
                        if (tile.hidden_treasure == true)
                        {
                            cout << "hooray!  you landed on a tile with a hidden treasure" << endl;
                            cout << "hit [Enter] to see what hidden treasure you found" << endl;
                            cin.ignore();
                            cin.get();
                            string treasure = board.getHiddenTreasure();

                            if (treasure == "stamina")
                            {
                                // add random stamina between 10 and 30
                                int random_number = random.generate(10, 30);
                                cout << "stamina refill: " << random_number << " units of stamina has been added." << endl;
                                players[player_index].addStamina(random_number);
                            }
                            else if (treasure == "gold")
                            {
                                // add random gold between 20 and 40
                                int random_number = random.generate(20, 40);
                                cout << "gold windfall: " << random_number << " gold has been added." << endl;
                                players[player_index].addGold(random_number);
                            }
                            else if (treasure == "robber")
                            {
                                // prevent another player from taking your gold while on the same tile
                                // note: the rules say you cannot have more than one player on a tile
                                cout << "rules unclear, the game will progress..." << endl;
                            }
                            else if (treasure == "candy-jellybean")
                            {
                                // add 50 units of stamina
                                cout << "candy acquisition-jellybean of vigor: the 'Jellybean of Vigor' candy has been added to your inventory." << endl;
                                candy.name = "Jellybean of Vigor";
                                candy.candy_type = "magical";
                                candy.description = "adds 50 units of stamina";
                                candy.effect_type = "stamina";
                                candy.effect_value = 50;
                                candy.price = 100000000;
                                players[player_index].addCandy(candy);
                            }
                            else if (treasure == "candy-truffle")
                            {
                                cout << "candy acquisition-treasure hunter's truffle: solve a riddle to unlock a hidden treasure!" << endl;
                                bool game_winner = games.playRiddles();
                                if (game_winner == true)
                                {
                                    cout << "you've unlocked a hidden treasure!" << endl;
                                }
                            }
                        }

                        if (tile.candy_store == true)
                        {
                            candy_store.visitCandyStore(players[player_index], candies);
                        }

                        // 40% chance of calamity
                        string calamity = board.getCalamity();
                        if (calamity != "")
                        {
                            if (calamity == "bandits")
                            {
                                // lose random gold (1-10)
                                int random_number = random.generate(1, 10);
                                players[player_index].removeGold(random_number);
                                cout << "oh no! candy bandits have swiped your gold coins!" << endl;
                                cout << RED << "you've lost " << random_number << " gold." << RESET << endl;
                            }
                            else if (calamity == "lollipop")
                            {
                                // lose one turn
                                // win rock, paper, scissors to undo
                                cout << "oh dear! you got lost in the lollipop labyrinth!" << endl;
                                cout << RED << "you've lost a turn!" << RESET << endl;
                                cout << "however, you can recover the damage by playing rock, paper, scissors." << endl;
                                cout << "if you win, you get the lost turn back!" << endl;
                                bool rps_winner = games.playRockPaperScissors();
                                if (rps_winner == true)
                                {
                                    cout << "hooray! you got your lost turn back!" << endl;
                                }
                                else
                                {
                                    cout << "oh no! you couldn't save your lost turn." << endl;
                                    players[player_index].addMissedTurns(1);
                                }
                            }
                            else if (calamity == "avalanche")
                            {
                                // lose random stamina (5-10)
                                // lose one turn
                                // win rock, paper, scissors to undo
                                int random_number = random.generate(5, 10);
                                cout << "watch out! a candy avalanche has struck!" << endl;
                                cout << RED << "you've lost a turn and " << random_number << " stamina!" << RESET << endl;
                                cout << "however, you can recover the damage by playing rock, paper, scissors!" << endl;
                                cout << "if you win, you get the lost resources back." << endl;
                                bool rps_winner = games.playRockPaperScissors();
                                if (rps_winner == true)
                                {
                                    cout << "hooray! you got your lost resources back!" << endl;
                                }
                                else
                                {
                                    cout << "oh no! you couldn't save your lost resources." << endl;
                                    players[player_index].addMissedTurns(1);
                                    players[player_index].removeStamina(random_number);
                                }
                            }
                            else if (calamity == "taffy")
                            {
                                // lose one turn
                                // use magic candy to undo
                                cout << "oops! you are stuck in a sticky taffy trap!" << endl;
                                cout << RED << "you've lost a turn!" << RESET << endl;
                                cout << "if you find yourself stuck in the sticky taffy trap, there's hope for a quick escape!" << endl;
                                cout << "if you have a magical candy in your inventory, you can use it to regain your lost turn." << endl;
                                string candy_name = "";

                                for (int i = 0; i < players[player_index].getCandies().size(); i++)
                                {
                                    if (players[player_index].getCandies()[i].candy_type == "magical")
                                    {
                                        candy_name = players[player_index].getCandies()[i].name;
                                        break;
                                    }
                                }
                                if (candy_name != "")
                                {
                                    cout << "you are lucky! you will not lose a turn because you possess a magical candy!" << endl;
                                    players[player_index].removeCandy(candy_name);
                                }
                                else
                                {
                                    cout << "uh oh! you do not have any magical candies!" << endl;
                                    cout << RED << "you've lost your turn!" << RESET << endl;
                                    players[player_index].addMissedTurns(1);
                                }
                            }
                        }
                        next_player = true;
                    }
                    else
                    {
                        cout << "hooray! you landed on a special tile" << endl;
                        cout << "hit [Enter] to see what special tile you landed on" << endl;
                        cin.ignore();
                        cin.get();
                    }

                    // special tile: shortcut
                    if (tile.tile_type == "shortcut")
                    {
                        // move forward 4 spaces
                        cout << "shortcut tile: your spirits soar as you're propelled four tiles ahead, closing in on the candy castle!" << endl;
                        winner = board.movePlayerToPosition(player_index, players, players[player_index].getBoardPosition() + 4);

                        next_player = true;
                    }

                    // special tile: icecream
                    if (tile.tile_type == "icecream")
                    {
                        cout << "ice cream stop tile: congratulations! you get a chance to draw a card again!" << endl;
                        // draw another card
                    }

                    // special tile: gumdrop
                    if (tile.tile_type == "gumdrop")
                    {
                        // move backwards 4 spaces
                        // lose random amount of gole (5-10)
                        int random_gold = random.generate(5, 10);

                        cout << RED << "gumdrop forest tile: oops, you move back 4 tiles and lose " << random_gold << " gold!" << RESET << endl;

                        players[player_index].removeGold(random_gold);
                        winner = board.movePlayerToPosition(player_index, players, players[player_index].getBoardPosition() - 4);
                        next_player = true;
                    }

                    // special tile: gingerbread
                    if (tile.tile_type == "gingerbread")
                    {
                        // move to previous postion
                        cout << RED << "gingerbread house tile: it's a bittersweet return to your previous location, accompanied by the forfeiture of one immunity candy." << RESET << endl;
                        winner = board.movePlayerToPosition(player_index, players, players[player_index].getPreviousBoardPosition());

                        // lose immunity candy (if you have one)
                        for (int i = 0; i < players[player_index].getCandies().size(); i++)
                        {
                            if (players[player_index].getCandies()[i].candy_type == "immunity")
                            {
                                players[player_index].removeCandy(players[player_index].getCandies()[i].name);
                                break;
                            }
                        }
                        next_player = true;
                    }

                    // special tile: gummy
                    if (tile.tile_type == "gummy")
                    {
                        cout << "gummy tile: you lose " << tile.gummy << " turns!" << endl;
                        players[player_index].addMissedTurns(tile.gummy);
                    }
                }
                // hailstorm: everyone moves back a somewhat random amount of tiles
                if (checkForHailStorm() == true)
                {
                    int random_number = random.generate(1, 10);
                    cout << RED << "uh oh! there is a marshmellow hailstorm! everyone moves back " << random_number << " spaces." << RESET << endl;
                    for (int i = 0; i < players.size(); i++)
                    {
                        winner = board.movePlayerToPosition(i, players, players[i].getBoardPosition() - random_number);
                    }
                }
                board.displayBoard(players);
                break;
            case 2: // use candy
                candy = getPlayerCandyChoice(players[player_index], candies, "");

                // the candy will not have a name if the player didn't choose a candy
                if (candy.name != "")
                {
                    if (candy.candy_type == "magical")
                    {
                        // all magical candies effect stamina
                        players[player_index].addStamina(candy.effect_value);
                        cout << "this candy added " << candy.effect_value << " stamina." << endl;
                    }
                    else if (candy.candy_type == "immunity")
                    {
                        // immunity is automatically used to counter poison
                        cout << "this candy was not used, it will be automatically used to counter a poison candy." << endl;
                    }
                    else if (candy.candy_type == "poison")
                    {
                        int player_poisoned;
                        string player_poisoned_choice;
                        bool valid_choice = false;
                        do
                        {
                            cout << "enter the player number you would like to poison: " << endl;
                            cin >> player_poisoned_choice;

                            switch (number_of_players)
                            {
                            case 1:
                                if (player_poisoned_choice == "1" || player_poisoned_choice == "2")
                                {
                                    player_poisoned = stoi(player_poisoned_choice) - 1;
                                    valid_choice = true;
                                }
                                break;
                            case 2:
                                if (player_poisoned_choice == "1" || player_poisoned_choice == "2" || player_poisoned_choice == "3")
                                {
                                    player_poisoned = stoi(player_poisoned_choice) - 1;
                                    valid_choice = true;
                                }
                                break;
                            case 3:
                                if (player_poisoned_choice == "1" || player_poisoned_choice == "2" || player_poisoned_choice == "3" || player_poisoned_choice == "4")
                                {
                                    player_poisoned = stoi(player_poisoned_choice) - 1;
                                    valid_choice = true;
                                }
                                break;
                            }
                            if (valid_choice == true && player_poisoned == player_index)
                            {
                                cout << "you cannot use poison on yourself, please choose another player: " << endl;
                                valid_choice = false;
                            }

                        } while (valid_choice == false);

                        // poison: -10 = mild, -15 = moderate, -20 = strong
                        // immunity: 1 = mild, 2 = mild/moderate, 3 = mild/moderate/strong
                        int immunity_candy_index = -1;
                        int immunity_candy_value = 4;
                        string immunity_candy_name = "";

                        switch (candy.effect_value)
                        {
                        case -10:
                            // check poisoned player to see if they have an immunity card with an effect value of 1, 2, or 3
                            for (int i = 0; i < players[player_poisoned].getCandies().size(); i++)
                            {
                                if (players[player_poisoned].getCandies()[i].candy_type == "immunity")
                                {
                                    if (players[player_poisoned].getCandies()[i].effect_value < immunity_candy_value)
                                    {
                                        immunity_candy_index = i;
                                        immunity_candy_value = players[player_poisoned].getCandies()[i].effect_value;
                                        immunity_candy_name = players[player_poisoned].getCandies()[i].name;
                                    }
                                }
                            }
                            if (immunity_candy_index > -1)
                            {
                                cout << "the player you are trying to poison had an immunity candy!" << endl;
                                players[player_poisoned].removeCandy(immunity_candy_name);
                            }
                            else
                            {
                                cout << "the player you poisoned lost " << candy.effect_value << " stamina" << endl;
                                players[player_poisoned].addStamina(candy.effect_value);
                            }
                            break;
                        case -15:
                            // check poisoned player to see if they have an immunity card with an effect value of 2 or 3
                            for (int i = 0; i < players[player_poisoned].getCandies().size(); i++)
                            {
                                if (players[player_poisoned].getCandies()[i].candy_type == "immunity" && players[player_poisoned].getCandies()[i].effect_value >= 2)
                                {
                                    if (players[player_poisoned].getCandies()[i].effect_value < immunity_candy_value)
                                    {
                                        immunity_candy_index = i;
                                        immunity_candy_value = players[player_poisoned].getCandies()[i].effect_value;
                                        immunity_candy_name = players[player_poisoned].getCandies()[i].name;
                                    }
                                }
                            }
                            if (immunity_candy_index > -1)
                            {
                                cout << "the player you are trying to poison had an immunity candy!" << endl;
                                players[player_poisoned].removeCandy(immunity_candy_name);
                            }
                            else
                            {
                                cout << "the player you poisoned lost " << candy.effect_value << " stamina" << endl;
                                players[player_poisoned].addStamina(candy.effect_value);
                            }
                            break;
                        case -20:
                            // check poisoned player to see if they have an immunity card with an effect value of 3
                            for (int i = 0; i < players[player_poisoned].getCandies().size(); i++)
                            {
                                if (players[player_poisoned].getCandies()[i].candy_type == "immunity" && players[player_poisoned].getCandies()[i].effect_value == 3)
                                {
                                    if (players[player_poisoned].getCandies()[i].effect_value < immunity_candy_value)
                                    {
                                        immunity_candy_index = i;
                                        immunity_candy_value = players[player_poisoned].getCandies()[i].effect_value;
                                        immunity_candy_name = players[player_poisoned].getCandies()[i].name;
                                    }
                                }
                            }
                            if (immunity_candy_index > -1)
                            {
                                cout << "the player you are trying to poison had an immunity candy!" << endl;
                                players[player_poisoned].removeCandy(immunity_candy_name);
                            }
                            else
                            {
                                cout << "the player you poisoned lost " << candy.effect_value << " stamina" << endl;
                                players[player_poisoned].addStamina(candy.effect_value);
                            }
                            break;
                        }
                    }
                    else if (candy.candy_type == "gummy")
                    {
                        // player gets to choose what tile to put the gummy candy on
                        int tile_number;
                        bool valid_choice = false;
                        do
                        {
                            cout << "enter a tile number between 1 and 82: " << endl;
                            cin >> tile_number;
                            if (tile_number >= 1 && tile_number <= 82)
                            {
                                valid_choice = true;
                            }
                        } while (valid_choice == false);
                        board.setGummyTile(tile_number, random.generate(1, 2));
                        cout << "the gummy tile has been set." << endl;
                    }

                    players[player_index].removeCandy(candy.name);
                }
                break;
                // todo: implement special immunity rules
            case 3: // show stats
                // get the player from the players array at the player_index and print stats
                players[player_index].printPlayerStats();
                break;
            }
        }
        if (next_player == true)
        {
            players[player_index].removeStamina(1);
            player_index = getNextPlayerIndex(player_index, number_of_players);
        }
    } while (winner == false);
    // todo: write player stats to a file

    ofstream os;
    os.open("GameStats.txt");
    for (int i = 0; i < players.size(); i++)
    {
        os << "here are " << players[i].getPlayerName() << "'s stats:" << endl;
        os << "===========================================================" << endl;
        os << "player name: " << players[i].getPlayerName() << endl;
        os << "player character: " << players[i].getCharacterName() << endl;
        os << "stamina: " << players[i].getStamina() << endl;
        os << "gold: " << players[i].getGold() << endl;
        os << "candies: " << endl;
        for (int j = 0; j < players[i].getCandies().size(); j++)
        {
            os << "[" << players[i].getCandies()[j].name << "] ";
        }
        os << endl;
        os << "===========================================================" << endl;
    }

    return 0;
}