#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>   // for sleep
#include <chrono>   // for delay

using namespace std;

const int SIZE = 50;

// Count alive neighbors with wrap-around
int countNeighbors(const vector<vector<bool>>& grid, int row, int col) {
    int count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue; // skip the cell itself

            int newRow = (row + dr + SIZE) % SIZE;
            int newCol = (col + dc + SIZE) % SIZE;

            if (grid[newRow][newCol])
                count++;
        }
    }
    return count;
}

int main() {
    vector<vector<bool>> grid(SIZE, vector<bool>(SIZE, false));
    srand(time(0));

    // Randomly populate grid
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col] = (rand() % 5 == 0);
        }
    }

    while (true) {
        system("cls"); // clear screen (Windows)

        // Print grid
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                cout << (grid[row][col] ? "#" : " ");
            }
            cout << endl;
        }

        // Prepare next generation
        vector<vector<bool>> newGrid = grid;
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                int neighbors = countNeighbors(grid, row, col);

                if (grid[row][col]) {
                    newGrid[row][col] = (neighbors == 2 || neighbors == 3);
                } else {
                    newGrid[row][col] = (neighbors == 3);
                }
            }
        }

        grid = newGrid;
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}
