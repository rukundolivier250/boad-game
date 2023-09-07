#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 6;
const int COLS = 7;

class Power4Game {
private:
    vector<vector<char>> board;
    char currentPlayer;

public:
    Power4Game() : board(ROWS, vector<char>(COLS, ' ')), currentPlayer('X') {}

    void printBoard() {
        cout << " 1 2 3 4 5 6 7" << endl;
        for (int i = 0; i < ROWS; ++i) {
            cout << "|";
            for (int j = 0; j < COLS; ++j) {
                cout << board[i][j] << "|";
            }
            cout << endl;
        }
        cout << "---------------" << endl;
    }

    bool isValidMove(int col) {
        return col >= 0 && col < COLS && board[0][col] == ' ';
    }

    void makeMove(int col) {
        for (int i = ROWS - 1; i >= 0; --i) {
            if (board[i][col] == ' ') {
                board[i][col] = currentPlayer;
                break;
            }
        }
    }

    bool checkWin() {
        // Check horizontally
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j <= COLS - 4; ++j) {
                if (board[i][j] == currentPlayer &&
                    board[i][j + 1] == currentPlayer &&
                    board[i][j + 2] == currentPlayer &&
                    board[i][j + 3] == currentPlayer) {
                    return true;
                }
            }
        }

        // Check vertically
        for (int i = 0; i <= ROWS - 4; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] == currentPlayer &&
                    board[i + 1][j] == currentPlayer &&
                    board[i + 2][j] == currentPlayer &&
                    board[i + 3][j] == currentPlayer) {
                    return true;
                }
            }
        }

        // Check diagonally (from bottom left to top right)
        for (int i = 3; i < ROWS; ++i) {
            for (int j = 0; j <= COLS - 4; ++j) {
                bool win = true;
                for (int k = 0; k < 4; ++k) {
                    if (board[i - k][j + k] != currentPlayer) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }
        }

        // Check diagonally (from top left to bottom right)
        for (int i = 0; i <= ROWS - 4; ++i) {
            for (int j = 0; j <= COLS - 4; ++j) {
                bool win = true;
                for (int k = 0; k < 4; ++k) {
                    if (board[i + k][j + k] != currentPlayer) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }
        }

        return false;
    }

    bool isBoardFull() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void play() {
        while (true) {
            printBoard();

            int col;
            do {
                cout << "Player " << currentPlayer << ", enter column (1-7): ";
                cin >> col;
                col--; // Adjust for 0-based indexing
            } while (!isValidMove(col));

            makeMove(col);

            if (checkWin()) {
                printBoard();
                cout << "Player " << currentPlayer << " wins!" << endl;
                break;
            } else if (isBoardFull()) {
                printBoard();
                cout << "It's a draw!" << endl;
                break;
            }

            switchPlayer();
        }
    }
};

int main() {
    Power4Game game;
    game.play();
    return 0;
}
