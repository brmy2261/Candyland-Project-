#include "Games.h"
#include "Random.h"
#include <fstream>

Games::Games()
{
    // load _riddles from Riddles.txt
    loadRiddles("Riddles.txt");
}

bool Games::playRockPaperScissors()
{
    /*
        1. ask the user to pick rock, paper, or scissors
        2. randomly generate a computer rock, paper, or scissors
        3. check the answer and return a bool that determines if the player won the game
    */
    string user_choice;
    Random _random;
    bool game_won = false;
    bool valid_choice = false;
    bool player_won = false;
    string game_choice[3] = {"rock", "paper", "scissors"};

    cout << "time to play rock, paper, scissors!" << endl;
    do
    {
        cout << "type rock, paper, or scissors to see if you won!: " << endl;
        do
        {
            cin >> user_choice;

            if (user_choice == "rock" || user_choice == "paper" || user_choice == "scissors")
            {
                valid_choice = true;
            }
            else if (user_choice != "rock" || user_choice != "paper" || user_choice != "scissors")
            {
                cout << "please type in rock, paper, or scissors!" << endl;
            }
        } while (valid_choice == false);

        int random_number = _random.generate(0, 2);
        string computer_choice = game_choice[random_number];

        if (user_choice == "rock")
        {
            if (computer_choice == "paper")
            {
                game_won = true;
                player_won = false;
            }
            else if (computer_choice == "scissors")
            {
                game_won = true;
                player_won = true;
            }
        }
        else if (user_choice == "paper")
        {
            if (computer_choice == "rock")
            {
                game_won = true;
                player_won = true;
            }
            else if (computer_choice == "scissors")
            {
                game_won = true;
                player_won = false;
            }
        }
        else
        {
            if (computer_choice == "paper")
            {
                game_won = true;
                player_won = true;
            }
            else if (computer_choice == "rock")
            {
                game_won = true;
                player_won = false;
            }
        }
        if (game_won == false)
        {
            cout << "there was a tie! you must play again." << endl;
        }
    } 
    while (game_won == false);

    if (player_won == true)
    {
        cout << "congratulations! you won rock, paper, scissors!" << endl;
    }
    else if (game_won == true)
    {
        cout << "oh no! the computer beat you in rock, paper, scissors!" << endl;
    }

    return player_won;
}

bool Games::playRiddles()
{
    /*
        1. pick a random riddle and show the question to the player
        2. check the answer and return a bool that determines if the player was correct or incorrect
    */
    Random _random;
    Riddle _riddle;
    string answer;

    int random_number = _random.generate(0, _riddles.size() - 1);
    _riddle = _riddles[random_number];

    cout << _riddle.question << endl;
    cin >> answer;

    if (answer == _riddle.answer)
    {
        cout << "that is correct!" << endl;

        return true;
    }
    else
    {
        cout << "the correct answer is: " << _riddle.answer << endl;
        return false;
    }
}

void Games::loadRiddles(string filename)
{
    // load _riddles from Riddles.txt
    vector<Riddle> riddles;
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        bool is_header = false;
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
                Riddle riddle;
                riddle.question = tokens[0];
                riddle.answer = tokens[1];
                _riddles.push_back(riddle);
            }
        }
        file.close();
    }
}