#include <iostream> // Enables input/output
#include <cstdlib>  // Enables rand()/srand()
#include <ctime>    // To seed random number generator with current time
#include <limits>   // Handles input errors

using namespace std; // Using standard namespace to avoid writing std:: before cout, cin, etc.

const int ROWS = 3; // Number of rows in the slot machine grid
const int COLS = 3; // Number of columns in the slot machine grid
const char SYMBOLS[] = {'A', 'O', 'X'}; // Symbols used in the slot machine

// Function to print the slot machine grid
void printGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) { // Loop through each row
        for (int j = 0; j < COLS; j++) { // Loop through each cell
            cout << grid[i][j] << " "; // Print the symbol
        }
        cout << endl; // Move to the next line
    }
}

// Function to spin the slot machine and fill the grid
void spin(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) { // Loop through each row
        for (int j = 0; j < COLS; j++) { // Loop through each cell
            grid[i][j] = SYMBOLS[rand() % 3]; // Randomly select a symbol
        }
    }
}

// Function to calculate winnings based on lines of identical symbols
int calculateWinnings(char grid[ROWS][COLS], int bet) {
    int lines = 0; // Initialize number of lines with identical symbols to 0

    // Check rows and columns
    for (int i = 0; i < ROWS; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) lines++; // Rows
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) lines++; // Columns
    }

    // Check diagonals
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) lines++; // Top-left to bottom-right
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) lines++; // Top-right to bottom-left

    // Full grid check
    bool fullGrid = true; // Assume full grid
    for (int i = 0; i < ROWS; i++) { // Loop through each row
        for (int j = 0; j < COLS; j++) { // Loop through each cell
            if (grid[i][j] != grid[0][0]) fullGrid = false; // If any symbol is different, grid is not full
        }
    }
    if (fullGrid) lines = 9; // Special case for full grid

    // Calculate winnings based on the number of lines
    switch (lines) {
        case 1: return 2 * bet; // One line
        case 2: return 3 * bet; // Two lines
        case 3: return 4 * bet; // Three lines
        case 4: return 5 * bet; // Four lines
        case 5: return 7 * bet; // Five lines
        case 9: return 10 * bet; // Full grid
        default: return 0; // No lines
    }
}

// Function to get a valid integer input within a range
int getValidInput(const string& prompt, int min, int max) {
    int input; // Variable to store user input
    while (true) { // Loop until valid input is entered
        cout << prompt; // Prompt user to enter input
        if (cin >> input && input >= min && input <= max) { // Check if input is valid
            break; // Exit the loop if valid input is received
        } else { // If input is invalid
            cout << "Invalid input, enter a number from " << min << " to " << max << "." << endl; // Prompt user to enter valid input
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore input buffer
        }
    }
    return input; // Return the valid input
}

// Function to get a valid choice (y/n)
char getValidChoice(const string& prompt) {
    char choice; // Variable to store user choice
    while (true) { // Loop until valid input is entered
        cout << prompt; // Prompt user to enter choice
        cin >> choice; // Input choice
        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') { // Check if input is valid
            break; // Exit the loop on valid input
        } else { // If input is invalid
            cout << "Invalid choice, enter 'y' or 'n'." << endl; // Prompt user to enter valid choice
        }
    }
    return choice; // Return the valid choice
}

int main() {
    srand(time(0)); // Seed the random number generator

    // Prompt user to select deposit amount
    int balance; // Variable to store balance
    balance = getValidInput( // Get valid input for balance
        "\n\n     Welcome to the Slots game.    \n"
        "                                       \n"
        "       Deposit amount options:         \n"
        "                                       \n"
        "    [1]  100 kr                        \n"
        "    [2]  300 kr                        \n"
        "    [3]  500 kr                        \n"
        "                                       \n"
        "       Select options: ",
        1, 3); // Set the range of valid input

    switch (balance) { // Set balance based on user input
        case 1: balance = 100; break; // If user selects 100 kr
        case 2: balance = 300; break; // If user selects 300 kr
        case 3: balance = 500; break; // If user selects 500 kr
    }

    while (balance > 0) { // Loop until balance is 0
        int bet; // Variable to store betting amount
        bet = getValidInput("\n   Enter betting amount: ", 1, balance); // Prompt user to enter betting amount

        char grid[ROWS][COLS]; // Initialize the slot machine grid
        spin(grid); // Spin the slot machine and fill the grid
        printGrid(grid); // Print the slot machine grid

        int winnings = calculateWinnings(grid, bet); // Calculate winnings based on the grid and bet
        if (winnings > 0) { // If the player wins
            balance += winnings; // Adds the winning amount to the balance
            cout << "Won: " << winnings << " kr. Total balance: " << balance << " kr\n"; // Displays the total balance after winning
        } else {
            balance -= bet; // Subtract the bet from the balance
            cout << "Lost. Total balance: " << balance << " kr\n"; // Displays the total balance after losing
        }

        if (balance <= 0) { // Check if balance is 0 or less
            cout << "Game over: Out of balance.\n"; // Displays game over-message if balance is 0 or less
            break; // Exit the loop if balance is 0 or less
        }

        char playAgain = getValidChoice("Play again [y/n]? "); // Ask user if they want to play again
        if (playAgain == 'n' || playAgain == 'N') { // Check if user wants to play again
            break; // Exit the loop if the user doesn't want to play again
        }
    }
    cout << "Thank you for playing! Your final balance is: " << balance << " kr\n"; // Displays the final balance
    return 0; // Returns 0 to indicate a successful execution
}
