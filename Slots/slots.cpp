#include <iostream>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding the random number generator

using namespace std;

const int ROWS = 3;
const int COLS = 3;
const char SYMBOLS[] = {'A', 'O', 'X'};

// Function to print the slot machine grid
void printGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to spin the slot machine and fill the grid
void spin(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = SYMBOLS[rand() % 3]; // Randomly select a symbol
        }
    }
}

// Function to calculate winnings based on lines of identical symbols
int calculateWinnings(char grid[ROWS][COLS], int bet) {
    int lines = 0;

    // Check rows and columns
    for (int i = 0; i < ROWS; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) lines++;
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) lines++;
    }

    // Check diagonals
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) lines++;
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) lines++;

    // Full grid check
    bool fullGrid = true;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] != grid[0][0]) fullGrid = false;
        }
    }
    if (fullGrid) lines = 9; // Special case for full grid

    // Calculate winnings based on the number of lines
    switch (lines) {
        case 1: return 2 * bet;
        case 2: return 3 * bet;
        case 3: return 4 * bet;
        case 4: return 5 * bet;
        case 5: return 7 * bet;
        case 9: return 10 * bet; // Full grid
        default: return 0;
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    int deposit;
    cout << "How much money do you want to deposit (100, 300, or 500 SEK): ";
    cin >> deposit;

    while (deposit > 0) {
        int bet;
        cout << "How much do you want to bet: ";
        cin >> bet;

        if (bet <= 0 || bet > deposit) {
            cout << "Invalid bet amount. Try again." << endl;
            continue;
        }

        char grid[ROWS][COLS];
        spin(grid);
        printGrid(grid);

        int winnings = calculateWinnings(grid, bet);
        if (winnings > 0) {
            cout << "Congratulations, you won " << winnings << " SEK!" << endl;
            deposit += winnings;
        } else {
            cout << "You didn't win this time." << endl;
        }

        deposit -= bet;
        cout << "Your remaining balance is " << deposit << " SEK." << endl;

        char playAgain;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain != 'y') break;
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
