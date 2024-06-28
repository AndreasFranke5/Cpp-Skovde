#include <iostream> // Enables input/output
#include <cstdlib> // Enables rand()/srand()
#include <ctime> // To seed random number generator with current time
#include <limits> // Handles input errors

using namespace std; // Using standard namespace to avoid writing std:: before cout, cin, etc.

int main() {
    srand(time(0)); // Seed random number generator with current time
    int balance = 1000; // Initializes starting balance to 1000 kr
    char playAgain = 'y'; // Variable to store user input to play again
    cout << "Welcome to the Roulette game. Starting balance: 1000 kr.\n";
    while (balance > 0 && (playAgain == 'y' || playAgain == 'Y')) { // Loop until balance is 0 or user chooses not to play again
        int betSelection; // Variable to store betting amount selection
        int bet; // Variable to store betting amount

        do {
            cout << "                                       " << endl;
            cout << "       Betting amount options:         " << endl;
            cout << "                                       " << endl;
            cout << "    [1]  100 kr                        " << endl;
            cout << "    [2]  300 kr                        " << endl;
            cout << "    [3]  500 kr                        " << endl;
            cout << "                                       " << endl;
            cout << "       Select betting amount: "; // Prompt user to select betting amount
            cin >> betSelection; // Input betting amount
            if (cin.fail() || betSelection < 1 || betSelection > 3) { // Check if input is invalid
                cout << "Invalid option, enter either 1, 2 or 3.\n"; // Error message
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear error flags and ignore input buffer
            } else {
                switch (betSelection) {
                    case 1: // If user selects 100 kr
                        bet = 100;
                        break;
                    case 2: // If user selects 300 kr
                        bet = 300;
                        break;
                    case 3: // If user selects 500 kr
                        bet = 500;
                        break;
                }
            } if (bet > balance) { // Check if bet is greater than balance
                cout << "Not enough balance.\n";
            } else {
                break; // Exit loop if valid input is entered
            }
        } while (true);
        int option; // Variable to store betting option
        do { 
            cout << "                                    " << endl;
            cout << "          Betting options:          " << endl;
            cout << "                                    " << endl;
            cout << "    [1]  Red                        " << endl;
            cout << "    [2]  Black                      " << endl;
            cout << "    [3]  Specific number            " << endl;
            cout << "                                    " << endl;
            cout << "          Select option: "; // Prompt user to select betting option
            cin >> option; // Input betting option
            if (cin.fail() || option < 1 || option > 3) { // Check if input is invalid
                cout << "Invalid option, enter either 1, 2 or 3.\n";
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore input buffer
            } else {
                break;
            }
        } while (true); // Loop until valid input is entered
        int betSpecificNum = 0; // Variable to store specific number to bet on
        if (option == 3) { // Check if user selected specific number
            do {
                cout << "Enter specific number to bet on [1-36]: "; // Prompt user to enter specific number
                cin >> betSpecificNum; 
                if (cin.fail() || betSpecificNum < 1 || betSpecificNum > 36) { // Check if input is invalid
                    cout << "Invalid option, enter number from 1 to 36.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore input buffer
                } else {
                    break;
                }
            } while (true);
        }
        int wheel = rand() % 36 + 1; // Generates random number between 1 and 36
        string color = (wheel % 2 == 0) ? "Black" : "Red"; // Assigns color to the wheel result
        cout << "                                                 " << endl;
        cout << "Wheel result: " << wheel << " (" << color << ")\n"; // Displays the result of the wheel
        bool won = false; // Variable to store if user won
        if (option == 1 && color == "Red") { // Check if user selected color and won
            won = true;
        } else if (option == 2 && color == "Black") { // Check if user selected color and won
            won = true;
        } else if (option == 3 && wheel == betSpecificNum) { // Check if user selected specific number and won
            won = true;
        }
        if (won) { // Check if user won
            int winnings = (option == 3) ? bet * 10 : bet * 2; // Calculates the winning amount
            balance += winnings; // Adds the winning amount to the balance
            cout << "Won: " << winnings << " kr. Total balance: " << balance << " kr\n"; // Displays the total balance after winning
        } else {
            balance -= bet; // Deducts the betting amount from the balance
            cout << "Lost. Total balance: " << balance << " kr\n"; // Displays the total balance after losing
        }
        if (balance <= 0) { // Check if balance is 0 or less
            cout << "Game over: Out of balance.\n"; // Displays game over-message if balance is 0 or less
            break;
        }
        do {
            cout << "Play again [y/n]? "; // Prompt user to play again
            cin >> playAgain; // Input to play again
            if (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N') { // Check if input is invalid
                cout << "Invalid option, enter either y or n.\n"; // Error message
            }
        } while (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N'); // Loop until valid input is entered
    cout << "Thank you for playing! Your final balance is: " << balance << " kr\n"; // Displays the final balance
    }
    return 0; // Returns 0 to indicate a successful execution
}
