#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// ============================================================
// ENUMERATION
// ============================================================

enum Difficulty
{
    EASY,
    HARD
};


// ============================================================
// CLASS 1: BOARD
// Responsible for board state and validation
// Suggested owner: MEMBER 1
// ============================================================

class Board
{
private:
    vector<vector<char>> grid;
    const int size;

public:

    // TODO - MEMBER 1:
    // Implement the constructor.
    // Initialize the board with the given size.
    // All cells should start empty.
    Board(int size = 3);

    // TODO - MEMBER 1:
    // Display the current board in the required format.
    // Include row/column coordinates and board borders.
    void display() const;

    // TODO - MEMBER 1:
    // Check whether the requested row and column are valid
    // and whether the selected cell is empty.
    bool isValidMove(int row, int col) const;

    // TODO - MEMBER 1:
    // If the move is valid, place the player's symbol in the
    // selected cell and return true.
    // Otherwise, do not change the board and return false.
    bool makeMove(int row, int col, char symbol);

    // TODO - MEMBER 1:
    // Check all possible winning conditions for the given symbol:
    // rows, columns, and both diagonals.
    bool checkWin(char symbol) const;

    // TODO - MEMBER 1:
    // Check whether every cell on the board is occupied.
    bool isFull() const;

    // TODO - MEMBER 1:
    // Return the character stored at the requested cell.
    char getCell(int row, int col) const;

    // TODO - MEMBER 1:
    // Clear all cells and return the board to its empty state.
    void reset();

    // TODO - MEMBER 1:
    // Return the board dimension.
    int getSize() const;
};


// ============================================================
// CLASS 2: PLAYER (ABSTRACT)
// Base class for all player entities
// Suggested owner: MEMBER 2
// ============================================================

class Player
{
protected:
    string name;
    char symbol;

public:

    // TODO - MEMBER 2:
    // Initialize the player's name and symbol.
    Player(const string& name, char symbol);

    // Pure virtual method.
    // Derived classes must implement how they select a move.
    virtual void getMove(int& row, int& col) = 0;

    // TODO - MEMBER 2:
    // Return the player's name.
    string getName() const;

    // TODO - MEMBER 2:
    // Return the player's symbol.
    char getSymbol() const;

    // TODO - MEMBER 2:
    // Update the player's name.
    void setName(const string& name);

    virtual ~Player() {}
};


// ============================================================
// CLASS 3: HUMAN PLAYER
// Suggested owner: MEMBER 3
//
// NOTE:
// The specification only explicitly defines the abstract Player
// class and AIPlayer class. A HumanPlayer class is added here as
// a supporting derived class so that Player::getMove() can be
// implemented properly for PvP/PvC modes.
// ============================================================

class HumanPlayer : public Player
{
public:

    // TODO - MEMBER 3:
    // Initialize the human player's name and symbol.
    HumanPlayer(const string& name, char symbol);

    // TODO - MEMBER 3:
    // Ask the human player for row and column input.
    // The specification requires coordinates from 1-3.
    // Convert them to the internal 0-based coordinates if needed.
    void getMove(int& row, int& col) override;
};


// ============================================================
// CLASS 4: AI PLAYER
// Computer opponent implementation
// Suggested owner: MEMBER 4
// ============================================================

class AIPlayer : public Player
{
private:
    Difficulty difficulty;

public:

    // TODO - MEMBER 4:
    // Initialize AI name, symbol, and difficulty.
    AIPlayer(const string& name, char symbol, Difficulty difficulty);

    // TODO - MEMBER 4:
    // Select the AI move according to the current difficulty.
    //
    // EASY:
    // Use getRandomMove().
    //
    // HARD:
    // Use getBestMove().
    void getMove(int& row, int& col) override;

    // TODO - MEMBER 4:
    // Change the AI difficulty.
    void setDifficulty(Difficulty newDifficulty);

    // TODO - MEMBER 4:
    // Select a random valid move from the board.
    // This is used for EASY difficulty.
    void getRandomMove(const Board& board, int& row, int& col) const;

    // TODO - MEMBER 5:
    // Find the optimal move for HARD difficulty.
    // Research and implement the minimax algorithm as required.
    void getBestMove(Board& board, int& row, int& col) const{

    };

    // TODO - MEMBER 5:
    // Evaluate the current board:
    // +10 for an AI win
    // -10 for an opponent win
    //  0 for draw/neutral state
    int evaluateBoard(const Board& board) const{
        //Check first if AI has won
        if(board.checkWin(this -> symbol)){
            return 10;
        }
        //Check which symbol the human opponent is to determine next steps
        char oppSymbol = (this -> symbol == 'X') ? 'O' : 'X';

        if(board.checkWin(oppSymbol)){
            return -10;
        }
        return 0;

    };
};


// ============================================================
// CLASS 5: GAME
// Responsible for game flow and coordination
// Suggested owner: MEMBER 6
// ============================================================

class Game
{
private:
    Board board;

    Player* player1;
    Player* player2;
    Player* currentPlayer;

    AIPlayer* aiPlayer;

    bool vsComputer;
    Difficulty difficulty;

public:

    // TODO - MEMBER 6:
    // Initialize the game with an empty board and null players.
    Game();

    // TODO - MEMBER 6:
    // Main game entry point.
    // Control the overall game flow.
    void start();

    // TODO - MEMBER 6:
    // Display the mode-selection menu:
    //
    // 1. Player vs Player
    // 2. Player vs Computer (Easy)
    // 3. Player vs Computer (Hard)
    // 4. Exit
    //
    // Read the user's choice and start the selected mode.
    void showMenu();

    // TODO - MEMBER 6:
    // Configure Player vs Player mode.
    // Ask for player names and create/configure two human players.
    void setupPvP();

    // TODO - MEMBER 6:
    // Configure Player vs Computer mode.
    // Create/configure the human player and AI player.
    void setupPvC(Difficulty difficulty);

    // TODO - MEMBER 6:
    // Change the current player between player1 and player2.
    void switchPlayer();

    // TODO - MEMBER 7:
    // Process a human player's turn.
    //
    // Requirements:
    // - Show whose turn it is.
    // - Ask for row and column.
    // - Validate input.
    // - Handle invalid input and allow recovery.
    // - Place the move on the board.
    void handleHumanMove(Player* player);

    // TODO - MEMBER 7:
    // Process the AI player's turn.
    //
    // Requirements:
    // - Execute the AI move calculation.
    // - Place the selected move on the board.
    // - Display appropriate feedback to the user.
    void handleAIMove(AIPlayer* aiPlayer);

    // TODO - MEMBER 7:
    // Check whether the game has ended.
    // A game ends when a player wins or the board is full.
    bool checkGameEnd();

    // TODO - MEMBER 7:
    // Display the result:
    // - Player win
    // - Computer win
    // - Draw
    void displayResult() const;

    // TODO - MEMBER 6:
    // Prepare the game for another round.
    // Reset the board and the required game state.
    void reset();
};


// ============================================================
// BOARD METHOD DEFINITIONS
// ============================================================

// TODO - MEMBER 1:
// Implement Board constructor.
Board::Board(int size)
    : grid(size, vector<char>(size, ' ')), size(size)
{
}


// TODO - MEMBER 1:
// Implement board display.
void Board::display() const
{
    // Display column numbers
    cout << "    ";
    for (int col = 0; col < size; col++)
    {
        cout << col + 1;

        if (col < size - 1)
        {
            cout << "   ";
        }
    }

    cout << endl;

    // Display rows
    for (int row = 0; row < size; row++)
    {
        cout << row + 1 << "   ";

        for (int col = 0; col < size; col++)
        {
            cout << grid[row][col];

            if (col < size - 1)
            {
                cout << " | ";
            }
        }

        cout << endl;

        // Display horizontal borders
        if (row < size - 1)
        {
            cout << "   ";

            for (int col = 0; col < size; col++)
            {
                cout << "---";

                if (col < size - 1)
                {
                    cout << "+";
                }
            }

            cout << endl;
        }
    }
}


// TODO - MEMBER 1:
// Implement move validation.
bool Board::isValidMove(int row, int col) const
{
    // Check if row and column are inside the board
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return false;
    }

    // Check if the selected cell is empty
    if (grid[row][col] != ' ')
    {
        return false;
    }

    return true;
}


// TODO - MEMBER 1:
// Implement move placement.
bool Board::makeMove(int row, int col, char symbol)
{
    // Check if the move is valid
    if (!isValidMove(row, col))
    {
        return false;
    }

    // Place the player's symbol
    grid[row][col] = symbol;

    return true;
}


// TODO - MEMBER 1:
// Implement win checking.
bool Board::checkWin(char symbol) const
{
    // Check rows
    for (int row = 0; row < size; row++)
    {
        bool win = true;

        for (int col = 0; col < size; col++)
        {
            if (grid[row][col] != symbol)
            {
                win = false;
                break;
            }
        }

        if (win)
        {
            return true;
        }
    }

    // Check columns
    for (int col = 0; col < size; col++)
    {
        bool win = true;

        for (int row = 0; row < size; row++)
        {
            if (grid[row][col] != symbol)
            {
                win = false;
                break;
            }
        }

        if (win)
        {
            return true;
        }
    }

    // Check main diagonal
    bool win = true;

    for (int i = 0; i < size; i++)
    {
        if (grid[i][i] != symbol)
        {
            win = false;
            break;
        }
    }

    if (win)
    {
        return true;
    }

    // Check opposite diagonal
    win = true;

    for (int i = 0; i < size; i++)
    {
        if (grid[i][size - 1 - i] != symbol)
        {
            win = false;
            break;
        }
    }

    if (win)
    {
        return true;
    }

    return false;
}


// TODO - MEMBER 1:
// Implement full-board checking.
bool Board::isFull() const
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (grid[row][col] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}


// TODO - MEMBER 1:
// Implement getCell.
char Board::getCell(int row, int col) const
{
    return grid[row][col];
}


// TODO - MEMBER 1:
// Implement board reset.
void Board::reset()
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            grid[row][col] = ' ';
        }
    }
}


// TODO - MEMBER 1:
// Implement getSize.
int Board::getSize() const
{
    return size;
}


// ============================================================
// PLAYER METHOD DEFINITIONS
// ============================================================

// TODO - MEMBER 2:
// Implement Player constructor.
Player::Player(const string& name, char symbol)
    : name(name), symbol(symbol)
{
}


// TODO - MEMBER 2:
// Implement getName.
string Player::getName() const
{
    return "";
}


// TODO - MEMBER 2:
// Implement getSymbol.
char Player::getSymbol() const
{
    return ' ';
}


// TODO - MEMBER 2:
// Implement setName.
void Player::setName(const string& name)
{
}


// ============================================================
// HUMAN PLAYER METHOD DEFINITIONS
// ============================================================

// TODO - MEMBER 3:
// Implement HumanPlayer constructor.
HumanPlayer::HumanPlayer(const string& name, char symbol)
    : Player(name, symbol)
{
}


// TODO - MEMBER 3:
// Implement human move input.
void HumanPlayer::getMove(int& row, int& col)
{
}


// ============================================================
// AI PLAYER METHOD DEFINITIONS
// ============================================================

// TODO - MEMBER 4:
// Implement AIPlayer constructor.
AIPlayer::AIPlayer(const string& name, char symbol, Difficulty difficulty)
    : Player(name, symbol), difficulty(difficulty)
{
}


// TODO - MEMBER 4:
// Implement AI move selection.
// Easy -> random move
// Hard -> best move / minimax
void AIPlayer::getMove(int& row, int& col)
{
}


// TODO - MEMBER 4:
// Implement difficulty setter.
void AIPlayer::setDifficulty(Difficulty newDifficulty)
{
}


// TODO - MEMBER 4:
// Implement random valid move selection.
void AIPlayer::getRandomMove(const Board& board, int& row, int& col) const
{
}


// TODO - MEMBER 5:
// Implement optimal move selection using minimax.
void AIPlayer::getBestMove(Board& board, int& row, int& col) const
{
}


// TODO - MEMBER 5:
// Implement board evaluation for AI.
int AIPlayer::evaluateBoard(const Board& board) const
{
    return 0;
}


// ============================================================
// GAME METHOD DEFINITIONS
// ============================================================

// TODO - MEMBER 6:
// Implement Game constructor.
// Initialize board, player pointers, current player,
// AI pointer, and game mode state.
Game::Game()
    : board(3),
      player1(nullptr),
      player2(nullptr),
      currentPlayer(nullptr),
      aiPlayer(nullptr),
      vsComputer(false),
      difficulty(EASY)
{
}


// TODO - MEMBER 6:
// Implement main game flow.
void Game::start()
{
}


// TODO - MEMBER 6:
// Implement menu display and menu selection.
void Game::showMenu()
{
}


// TODO - MEMBER 6:
// Implement Player vs Player setup.
void Game::setupPvP()
{
}


// TODO - MEMBER 6:
// Implement Player vs Computer setup.
void Game::setupPvC(Difficulty difficulty)
{
}


// TODO - MEMBER 6:
// Implement player switching.
void Game::switchPlayer()
{
}


// TODO - MEMBER 7:
// Implement human move handling.
void Game::handleHumanMove(Player* player)
{
}


// TODO - MEMBER 7:
// Implement AI move handling.
void Game::handleAIMove(AIPlayer* aiPlayer)
{
}


// TODO - MEMBER 7:
// Implement game-end checking.
bool Game::checkGameEnd()
{
    return false;
}


// TODO - MEMBER 7:
// Implement result display.
void Game::displayResult() const
{
}


// TODO - MEMBER 6:
// Implement game reset for a new round.
void Game::reset()
{
}


// ============================================================
// MAIN FUNCTION
// owner: MEMBER 6
// ============================================================

int main()
{
    Game game;
    game.start();

    return 0;
}
