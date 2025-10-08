#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    vector<vector<bool>> grid(50, vector<bool>(50, false));
    
    srand(time(0));
    
    for (int row = 0; row < 50; row++) {
        for (int col = 0; col < 50; col++) {
            grid[row][col] = (rand() % 5 == 0);;
    }
}

    for (int row = 0; row < 50; row++) {
        for (int col = 0; col < 50; col++) {
            if (grid[row][col])
                cout << "#";
            else
                cout << " ";
        }
        cout << endl;
    }
}