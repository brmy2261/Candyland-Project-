#include "Player.h"

Player::Player()
{
    _boardPosition = 0;
    _previousBoardPosition = 0;
    _missedTurns = 0;
}

int Player::getPlayerNumber()
{
    return _number;
}

string Player::getPlayerName()
{
    return _name;
}

string Player::getCharacterName()
{
    return _character_name;
}

int Player::getStamina()
{
    return _stamina;
}

int Player::getGold()
{
    return _gold;
}

vector<Candy> Player::getCandies()
{
    return _candies;
}

int Player:: getBoardPosition()
{
    return _boardPosition;
}

int Player::getPreviousBoardPosition()
{
    return _previousBoardPosition;
}

int Player::getMissedTurns()
{
    return _missedTurns;
}

void Player::setPlayerNumber(int number)
{
    _number = number;
}

void Player::setPlayerName(string name)
{
    _name = name;
}

void Player::setCharacterName(string characterName)
{
    _character_name = characterName;
}

void Player::setStamina(int stamina)
{
    _stamina = stamina;
}

void Player::setGold(int gold)
{
    _gold = gold;
}

void Player::setCandies(vector<Candy> candies)
{
    _candies = candies;
}

void Player::setBoardPosition(int boardPosition)
{
    _boardPosition = boardPosition;
}

void Player::setPreviousBoardPosition(int previousBoardPosition)
{
    _previousBoardPosition = previousBoardPosition;
}

void Player::setMissedTurns(int missedTurns)
{
    _missedTurns = missedTurns;
}

void Player::addStamina(int stamina)
{
    if (_stamina + stamina > 100) 
    {
        _stamina = 100;
    } 
    else 
    {
        _stamina = _stamina + stamina;
    }
}

void Player::removeStamina(int stamina)
{
    if (_stamina - stamina > 0) 
    {
        _stamina = _stamina - stamina;
    } 
    else 
    {
        _stamina = 0;
    }
}

void Player::addGold(int gold)
{
    if (_gold + gold > 100) 
    {
        _gold = 100;
    } 
    else 
    {
        _gold = _gold + gold;
    }
}

void Player::removeGold(int gold)
{
    if (_gold - gold > 0) 
    {
        _gold = _gold - gold;
    } 
    else 
    {
        _gold = 0;
    }
}

void Player::addCandy(Candy candy)
{
    _candies.push_back(candy);
}

void Player::removeCandy(string candyName)
{
    for (int i = 0; i < _candies.size(); i++)
    {
        if (candyName == _candies[i].name)
        {
            _candies.erase(_candies.begin() + i);
        }
    }
}

void Player::addMissedTurns(int missedTurns)
{
    _missedTurns = _missedTurns + missedTurns;
}

void Player::removeMissedTurns(int missedTurns)
{
    if (_missedTurns - missedTurns < 0)
    {
        _missedTurns = 0;
    }
    else
    {
        _missedTurns = _missedTurns - missedTurns;
    }
}

void Player::printPlayerStats()
{
    cout << "here are " << getPlayerName() << "'s stats:" << endl;
    cout << "===========================================================" << endl;
    cout << "player name: " << getPlayerName() << endl;
    cout << "player character: " << getCharacterName() << endl;
    cout << "stamina: " << getStamina() << endl;
    cout << "gold: " << getGold() << endl;
    cout << "candies: " << endl;
    for (int i = 0; i < getCandies().size(); i++)
    {
        cout << "[" << getCandies()[i].name << "] ";
    }
    cout << endl;
    cout << "===========================================================" << endl;
}