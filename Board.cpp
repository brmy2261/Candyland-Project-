#include "Board.h"
#include "Colors.h"
#include "Random.h"

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular", false, false, false, 0};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    setCandyStores();
    setSpecialTiles();
    setHiddenTreasure();
}

void Board::setCandyStores()
{
    bool found_magenta = false;
    bool found_green = false;
    bool found_blue = false;
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        if (_tiles[i].color == MAGENTA && i < 27 && found_magenta == false)
        {
            _tiles[i].candy_store = true;
            found_magenta = true;
        }

        if (_tiles[i].color == GREEN && i >= 27 && i < 54 && found_green == false)
        {
            _tiles[i].candy_store = true;
            found_green = true;
        }
        if (_tiles[i].color == BLUE && i >= 54 && found_blue == false)
        {
            _tiles[i].candy_store = true;
            found_blue = true;
        }
    }
}

void Board::setSpecialTiles()
{
    int special_tiles = _SPECIAL_TILE;
    int tile_index;
    int random_number;
    do
    {
        tile_index = _random.generate(0, _BOARD_SIZE - 1);

        if (_tiles[tile_index].tile_type == "regular" && _tiles[tile_index].candy_store == false)
        {
            random_number = _random.generate(1, 4);
            switch (random_number)
            {
            case 1:
                _tiles[tile_index].tile_type = "shortcut";
                break;
            case 2:
                _tiles[tile_index].tile_type = "gingerbread";
                break;
            case 3:
                _tiles[tile_index].tile_type = "gumdrop";
                break;
            case 4:
                _tiles[tile_index].tile_type = "icecream";
                break;
            }
            special_tiles--;
        }
    } while (special_tiles > 0);
}

void Board::setGummyTile(int tileIndex, int lostTurns)
{
    Tile tile = _tiles[tileIndex];
    tile.gummy = lostTurns;
    _tiles[tileIndex] = tile;    
}

void Board::setHiddenTreasure()
{
    int treasure_tiles = _TREASURE_TILE;
    int tile_index;
    int random_number;
    do
    {
        tile_index = _random.generate(0, _BOARD_SIZE - 1);

        if (_tiles[tile_index].tile_type == "regular" && _tiles[tile_index].candy_store == false)
        {
            _tiles[tile_index].hidden_treasure = true;
            treasure_tiles--;
        }
    } while (treasure_tiles > 0);
}

void Board::displayTile(int position)
{
    string tile_text = " ";

    for (int i = 0; i < _players.size(); i++)
    {
        if (_players[i].getBoardPosition() == position)
        {
            tile_text = to_string(i + 1);
            break;
        }
    }

    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " " << tile_text << " " << RESET;
}

void Board::displayBoard(vector<Player> players)
{
    _players = players;

    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;

    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }

    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;

    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }

    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

bool Board::movePlayerByCard(int playerIndex, vector<Player> &players, Card card)
{
    int tile_index = -1;
    int number_of_tiles = 1;

    if (card.isX2 == true)
    {
        number_of_tiles = 2;
    }

    for (int i = players[playerIndex].getBoardPosition() + 1; i < _BOARD_SIZE; i++)
    {
        if (_tiles[i].color == card.color)
        {
            number_of_tiles--;
            if (number_of_tiles == 0)
            {
                tile_index = i;
                break;
            }
        }
    }

    if (tile_index == -1)
    {
        // this means that there was no tile found, therefore, player reached the castle
        players[playerIndex].setPreviousBoardPosition(players[playerIndex].getBoardPosition());
        players[playerIndex].setBoardPosition(_BOARD_SIZE);
        return true;
    }
    else
    {
        bool is_occupied = true;
        do
        {
            is_occupied = false;
            for (int i = 0; i < players.size(); i++)
            {
                if (i != playerIndex && players[i].getBoardPosition() == tile_index)
                {
                    tile_index--;
                    is_occupied = true;
                    break;
                }
            }
        } while (is_occupied == true);

        // set the player position to tile index
        players[playerIndex].setPreviousBoardPosition(players[playerIndex].getBoardPosition());
        players[playerIndex].setBoardPosition(tile_index);
        return false;
    }
}

bool Board::movePlayerToPosition(int playerIndex, vector<Player> &players, int newPosition)
{
    if (newPosition < 0)
    {
        newPosition = 0;
    }

    if (newPosition > _BOARD_SIZE)
    {
        newPosition = _BOARD_SIZE;
    }

    if (newPosition > 0)
    {
        bool is_occupied = true;
        do
        {
            is_occupied = false;
            for (int i = 0; i < players.size(); i++)
            {
                if (i != playerIndex && players[i].getBoardPosition() == newPosition)
                {
                    newPosition--;
                    is_occupied = true;
                    break;
                }
            }
        } while (is_occupied == true);
    }

    // set the player position to tile index
    players[playerIndex].setPreviousBoardPosition(players[playerIndex].getBoardPosition());
    players[playerIndex].setBoardPosition(newPosition);

    if (newPosition >= _BOARD_SIZE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Tile Board::getTile(int position)
{
    return _tiles[position];
}

string Board::getHiddenTreasure()
{
    // stamina (30%), gold (10%), robber (30%), candy-jellybean (21%), candy-truffle (9%)

    int random_number = _random.generate(1, 100);

    if (random_number >= 1 && random_number <= 30)
    {
        return "stamina";
    }
    else if (random_number >= 31 && random_number < 40)
    {
        return "gold";
    }
    else if (random_number >= 41 && random_number < 70)
    {
        return "robber";
    }
    else if (random_number >= 71 && random_number < 81)
    {
        return "candy-jellybean";
    }
    else
    {
        return "candy-truffle";
    }
}

string Board::getCalamity()
{
    // 40% chance of getting a calamity
    int random_number = _random.generate(1, 100);

    if (random_number >= 1 && random_number <= 40)
    {
        random_number = _random.generate(1, 100);
        if (random_number >= 1 && random_number <= 30) // bandits (30%),
        {
            return "bandits";
        }
        else if (random_number >= 31 && random_number <= 65) // lollipop (35%)
        {
            return "lollipop";
        }
        else if (random_number >= 66 && random_number <= 80) // avalanche (15%)
        {
            return "avalanche";
        }
        else // taffy (20%)
        {
            return "taffy";
        }
    }
    else
    {
        return "";
    }
}