#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>   // for sleep
#include <chrono>   // for delay

using namespace std;

const int SIZE = 50;

// Count alive neighbors with wrap-around (cells are int: 0 or 1)
int countNeighbors(const vector<vector<int>>& grid, int row, int col) {
    int count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue; // skip the cell itself

            int newRow = (row + dr + SIZE) % SIZE;
            int newCol = (col + dc + SIZE) % SIZE;

            if (grid[newRow][newCol] == 1)
                count++;
        }
    }
    return count;
}

int main() {
    vector<vector<int>> grid(SIZE, vector<int>(SIZE, 0));
    srand((unsigned)time(0));

    // Randomly populate grid (~20% alive)
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col] = (rand() % 5 == 0) ? 1 : 0;
        }
    }

    while (true) {
        system("cls"); // clear screen on Windows; replace with ANSI if you want cross-platform

        // Print grid ('#' for alive, space for dead)
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                cout << (grid[row][col] == 1 ? "#" : " ");
            }
            cout << endl;
        }

        // Compute next generation
        vector<vector<int>> newGrid = grid; // start as a copy
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                int neighbors = countNeighbors(grid, row, col);

                if (grid[row][col] == 1) {
                    // alive stays alive only with 2 or 3 neighbors
                    newGrid[row][col] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
                } else {
                    // dead becomes alive with exactly 3 neighbors
                    newGrid[row][col] = (neighbors == 3) ? 1 : 0;
                }
            }
        }

        grid = move(newGrid); // faster swap/copy
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    return 0;
}
