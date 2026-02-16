#include <iostream>
#include <string>

using namespace std;

class Game {
protected:
    string player1Name;
    string player2Name;
    bool isPlayer1Turn;

public:
    Game() {
        cout << "Enter Player 1 name: ";
        cin >> player1Name;
        cout << "Enter Player 2 name: ";
        cin >> player2Name;
        cout << endl;

        isPlayer1Turn = true;
    }

    virtual void drawBoard() = 0;
    virtual bool checkWin(char player) = 0;
    virtual bool checkDraw() = 0;
    virtual void makeMove(int position, char player) = 0;
    virtual void getNextMove(int& position, const string& playerName) = 0;
    virtual void playGame() = 0;
};

class TicTacToe : public Game {
private:
    char board[3][3];
    char player1Symbol;
    char player2Symbol;
    static int player1Moves;
    static int player2Moves;

public:
    TicTacToe() : Game() {
        // Assign symbols to players
        player1Symbol = 'X';
        player2Symbol = 'O';

        // Initialize the board with empty spaces
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
            }
        }
        player1Moves = 0;
        player2Moves = 0;
    }

    void drawBoard() {
        cout << "-------------" << endl;
        for (int i = 0; i < 3; ++i) {
            cout << "| ";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j] << " | ";
            }
            cout << endl << "-------------" << endl;
        }
    }

    bool checkWin(char player) {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;
        }

        // Check columns
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
                return true;
        }

        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;

        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;

        return false;
    }

    bool checkDraw() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    void makeMove(int position, char player) {
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;
        board[row][col] = player;

        // Increment the number of moves for the respective player
        if (player == player1Symbol)
            player1Moves++;
        else if (player == player2Symbol)
            player2Moves++;
    }

    void getNextMove(int& position, const string& playerName) {
        cout << playerName << ", enter your move (1-9): ";
        cin >> position;
        cout << endl;
    }

    void playGame() {
        int position;

        while (true) {
            drawBoard();

            if (isPlayer1Turn)
                getNextMove(position, player1Name);
            else
                getNextMove(position, player2Name);

            // Check if the move is valid
            if (position < 1 || position > 9) {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            int row = (position - 1) / 3;
            int col = (position - 1) % 3;

            if (board[row][col] != ' ') {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            // Make the move
            if (isPlayer1Turn)
                makeMove(position, player1Symbol);
            else
                makeMove(position, player2Symbol);

            // Check if the current player has won
            if (checkWin(isPlayer1Turn ? player1Symbol : player2Symbol)) {
                drawBoard();
                string winningPlayerName = isPlayer1Turn ? player1Name : player2Name;
                int winningPlayerMoves = isPlayer1Turn ? player1Moves : player2Moves;
                cout << winningPlayerName << " wins in " << winningPlayerMoves << " moves!" << endl;
                break;
            }

            // Check if it's a draw
            if (checkDraw()) {
                drawBoard();
                cout << "It's a draw!" << endl;
                break;
            }

            // Switch to the next player
            isPlayer1Turn = !isPlayer1Turn;
        }
    }

    static int getMoves(char player) {
        if (player == 'X')
            return player1Moves;
        else if (player == 'O')
            return player2Moves;
        else
            return 0;
    }
};

// Initialize static member variables
int TicTacToe::player1Moves = 0;
int TicTacToe::player2Moves = 0;

int main() {
    cout << "Tic Tac Toe" << endl;

    TicTacToe game;
    game.playGame();

    return 0;
}
