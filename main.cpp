#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class GameOfLife {
private:
    int width;
    int height;
    vector<vector<int>> board;
    vector<vector<int>> new_board;

    int countAliveNeighbors(int x, int y) {
        int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
        int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
        int aliveNeighbors = 0;

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                aliveNeighbors += board[nx][ny];
            }
        }

        return aliveNeighbors;
    }

    void updateBoard() {
        new_board = board;  // Copy current board state to new_board

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int aliveNeighbors = countAliveNeighbors(x, y);

                if (board[x][y] == 1) {  // If cell is alive
                    if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                        new_board[x][y] = 0;  // Cell dies
                    }
                }
                else {  // If cell is dead
                    if (aliveNeighbors == 3) {
                        new_board[x][y] = 1;  // Cell becomes alive
                    }
                }
            }
        }
    }

    bool isStable() {
        return board == new_board;
    }

    bool hasAliveCells() {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (board[i][j] == 1) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    GameOfLife(int w, int h) : width(w), height(h), board(w, vector<int>(h, 0)), new_board(w, vector<int>(h, 0)) {}

    void initialize(int aliveCells) {
        srand(time(0)); // Seed for random number generation
        while (aliveCells > 0) {
            int x = rand() % width;
            int y = rand() % height;
            if (board[x][y] == 0) {
                board[x][y] = 1; // Set cell to 1 (alive)
                aliveCells--;
            }
        }
    }

    void display() {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                cout << (board[i][j] ? "1 " : "0 ");
            }
            cout << endl;
        }
        cout << endl;
    }

    void play() {
        while (true) {
            display();

            if (!hasAliveCells()) {
                cout << "No more alive cells. Game over." << endl;
                break;
            }

            updateBoard();

            if (isStable()) {
                cout << "The board has reached a stable state. Game over." << endl;
                break;
            }

            board = new_board;  // Update the board with new state

            cout << "Press Enter to continue..." << endl;
            cin.ignore();
        }
    }
};

int main() {
    int width, height, aliveCells;

    cout << "Enter the width of the board: ";
    cin >> width;

    cout << "Enter the height of the board: ";
    cin >> height;

    cout << "Enter the number of alive cells: ";
    cin >> aliveCells;

    if (aliveCells > width * height) {
        cout << "Number of alive cells cannot be more than the total number of cells on the board." << endl;
        return 1;
    }

    GameOfLife game(width, height);
    game.initialize(aliveCells);
    game.play();
    return 0;
}
