#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

int main() {
    srand(time(0));
    int funds = 1000;
    cout << "Welcome to the Roulette game. Starting funds: 1000 kr.\n";
    while (funds > 0) {
        int bet;
        do {
            cout << "Select bet amount [ 100 | 300 | 500 ]: ";
            cin >> bet;
            if (cin.fail() || (bet != 100 && bet != 300 && bet != 500)) {
                cout << "Invalid bet, enter either 100, 300 or 500.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            } else if (bet > funds) {
                cout << "Not enough funds.\n";
            } else {
                break;
            }
        } while (true);
        int option;
        do {
            cout << "Betting options:" << endl;
            cout << "1: Red" << endl;
            cout << "2: Black" << endl;
            cout << "3: Specific number (1-36)";
            cout << "Select option [ 1 | 2 | 3 ]: ";
            cin >> option;
            if (cin.fail() || option < 1 || option > 3) {
                cout << "Invalid option, enter either 1, 2 or 3.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        } while (true);
        int betSpecificNum = 0;
        if (option == 3) {
            do {
                cout << "Enter specific number to bet on [1-36]: ";
                cin >> betSpecificNum;
                if (cin.fail() || betSpecificNum < 1 || betSpecificNum > 36) {
                    cout << "Invalid number, enter value from 1 to 36.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    break;
                }
            } while (true);
        }
        int wheel = rand() % 36 + 1;
        string color = (wheel % 2 == 0) ? "Black" : "Red";
        cout << "Wheel result: " << wheel << " (" << color << ")\n";
        bool win = false;
        if (option == 1 && color == "Red") {
            win = true;
        } else if (option == 2 && color == "Black") {
            win = true;
        } else if (option == 3 && wheel == betSpecificNum) {
            win = true;
        }
        if (win) {
            int winnings = (option == 3) ? bet * 10 : bet * 2;
            funds += winnings;
            cout << "Win: " << winnings << " kr. Total funds: " << funds << " kr\n";
        } else {
            funds -= bet;
            cout << "Lose. Total funds: " << funds << " kr\n";
        }
    }
    cout << "Out of funds, game over.\n";
    return 0;
}
