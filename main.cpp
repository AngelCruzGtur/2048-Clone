#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>  

using namespace std;

class Game2048 {
public:
    // Constructor: Initializes the game grid and adds the first two tiles.
    Game2048() 
    {
        grid = vector< vector<int> >(4, vector<int>(4, 0));
        srand(time(0));
        addNewTile();  // Add the first tile randomly
        addNewTile();  // Add the second tile randomly
    }

    // Play function: The main game loop where the user inputs their moves.
    void play() 
    {
        char move;
        while (true) 
        {
            printGrid();
            cout << "\n\nEnter move (W - Up, A - Left, S - Down, D - Right, Q - Quit): ";
            cin >> move;

            if (move == 'Q' || move == 'q') 
            {
                break;
            }

            bool moved = false;
            switch (move) 
            {
                case 'W': case 'w':
                    moved = slideUp();
                    break;
                case 'A': case 'a':
                    moved = slideLeft();
                    break;
                case 'S': case 's':
                    moved = slideDown();
                    break;
                case 'D': case 'd':
                    moved = slideRight();
                    break;
                default:
                    cout << "Invalid move! Please use W, A, S, D, or Q to quit." << endl;
                    continue;
            }

            if (moved) 
            {
                addNewTile();
            }

            // Check for game over condition
            if (isGameOver()) 
            {
                printGrid();
                cout << "\nGAME OVER!" << endl;
                break;
            }
        }
    }

private:
    vector< vector<int> > grid;

    // Prints the current state of the game grid.
    void printGrid() 
    {
        system("clear");  

        cout << "-----------------------------\n";
        cout << setw(17) << "2048\n"; 
        cout << "-----------------------------\n";

        for (int i = 0; i < 4; i++) 
        {
            cout << setw(50); 
            for (int j = 0; j < 4; j++) 
            {
                cout << setw(5) << (grid[i][j] == 0 ? "." : to_string(grid[i][j])) << " ";
            }
            cout << endl;
        }
        cout << "-----------------------------\n";
    }

    // Adds a new tile (2 or 4) at a random empty position on the grid.
    void addNewTile() 
    {
        vector< pair<int, int> > emptyCells;
        for (int i = 0; i < 4; i++) 
        {
            for (int j = 0; j < 4; j++) 
            {
                if (grid[i][j] == 0) 
                {
                    emptyCells.push_back(pair<int, int>(i, j));
                }
            }
        }

        if (emptyCells.empty()) return;

        int index = rand() % emptyCells.size();
        pair<int, int> cell = emptyCells[index];
        
        // Randomly set the new tile to 2 or 4 with a 90% chance of being 2
        grid[cell.first][cell.second] = (rand() % 10 == 0) ? 4 : 2;
    }

    // Slides and merges tiles upwards if possible, returns whether a move was made.
    bool slideUp() 
    {
        bool moved = false;
        for (int j = 0; j < 4; j++) 
        {
            vector<int> temp;
            // Collect non-zero tiles from top to bottom
            for (int i = 0; i < 4; i++) 
            {
                if (grid[i][j] != 0) 
                {
                    temp.push_back(grid[i][j]);
                }
            }
            vector<int> merged(4, 0);
            int index = 0;

            // Slide and merge tiles
            for (int i = 0; i < temp.size(); i++) 
            {
                if (i < temp.size() - 1 && temp[i] == temp[i + 1]) 
                {
                    merged[index] = temp[i] * 2;
                    i++;  // Skip next tile after merging
                } 
                else 
                {
                    merged[index] = temp[i];
                }
                index++;
            }

            // Place the merged tiles back to the grid
            for (int i = 0; i < 4; i++) 
            {
                if (grid[i][j] != merged[i]) 
                {
                    moved = true;
                }
                grid[i][j] = merged[i];
            }
        }
        return moved;
    }

    // Slides and merges tiles to the left if possible, returns whether a move was made.
    bool slideLeft() 
    {
        bool moved = false;
        for (int i = 0; i < 4; i++) 
        {
            vector<int> temp;
            // Collect non-zero tiles from left to right
            for (int j = 0; j < 4; j++) 
            {
                if (grid[i][j] != 0) 
                {
                    temp.push_back(grid[i][j]);
                }
            }
            vector<int> merged(4, 0);
            int index = 0;

            // Slide and merge tiles
            for (int j = 0; j < temp.size(); j++) 
            {
                if (j < temp.size() - 1 && temp[j] == temp[j + 1]) 
                {
                    merged[index] = temp[j] * 2;
                    j++;  // Skip next tile after merging
                } 
                else 
                {
                    merged[index] = temp[j];
                }
                index++;
            }

            // Place the merged tiles back to the grid
            for (int j = 0; j < 4; j++) 
            {
                if (grid[i][j] != merged[j]) 
                {
                    moved = true;
                }
                grid[i][j] = merged[j];
            }
        }
        return moved;
    }

    // Slides and merges tiles downwards if possible, returns whether a move was made.
    bool slideDown() 
    {
        bool moved = false;
        for (int j = 0; j < 4; j++) 
        {
            vector<int> temp;
            // Collect non-zero tiles from bottom to top
            for (int i = 3; i >= 0; i--) 
            {
                if (grid[i][j] != 0) 
                {
                    temp.push_back(grid[i][j]);
                }
            }
            vector<int> merged(4, 0);
            int index = 3;

            // Slide and merge tiles
            for (int i = 0; i < temp.size(); i++) 
            {
                if (i < temp.size() - 1 && temp[i] == temp[i + 1]) 
                {
                    merged[index] = temp[i] * 2;
                    i++;  // Skip next tile after merging
                } 
                else 
                {
                    merged[index] = temp[i];
                }
                index--;
            }

            // Place the merged tiles back to the grid
            for (int i = 0; i < 4; i++) 
            {
                if (grid[i][j] != merged[i]) 
                {
                    moved = true;
                }
                grid[i][j] = merged[i];
            }
        }
        return moved;
    }

    // Slides and merges tiles to the right if possible, returns whether a move was made.
    bool slideRight() 
    {
        bool moved = false;
        for (int i = 0; i < 4; i++) 
        {
            vector<int> temp;
            // Collect non-zero tiles from right to left
            for (int j = 3; j >= 0; j--) 
            {
                if (grid[i][j] != 0) 
                {
                    temp.push_back(grid[i][j]);
                }
            }
            vector<int> merged(4, 0);
            int index = 3;

            // Slide and merge tiles
            for (int j = 0; j < temp.size(); j++) 
            {
                if (j < temp.size() - 1 && temp[j] == temp[j + 1]) 
                {
                    merged[index] = temp[j] * 2;
                    j++;  // Skip next tile after merging
                } 
                else 
                {
                    merged[index] = temp[j];
                }
                index--;
            }

            // Place the merged tiles back to the grid
            for (int j = 0; j < 4; j++) 
            {
                if (grid[i][j] != merged[j]) 
                {
                    moved = true;
                }
                grid[i][j] = merged[j];
            }
        }
        return moved;
    }

    // Checks if the game is over (no valid moves left).
    bool isGameOver() 
    {
        for (int i = 0; i < 4; i++) 
        {
            for (int j = 0; j < 4; j++) 
            {
                if (grid[i][j] == 0) return false;  // There's an empty space, so game isn't over

                // Check adjacent cells for possible merges
                if (i < 3 && grid[i][j] == grid[i + 1][j]) return false;  // Can merge up/down
                if (j < 3 && grid[i][j] == grid[i][j + 1]) return false;  // Can merge left/right
            }
        }

        return true;  // Grid is full and no merges are possible
    }
};

int main() 
{
    Game2048 game;
    game.play();
    return 0;
}
