#include <iostream>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

// Struct to hold card details
struct Number {
    int num1, num2, sum, extraCard;
};

// Function prototypes
void printCard1(int num1, int num2, int num3, int sum);
void printCard2(int num1, int num2, int sum);
bool playAgain(char x, int money);
int winnerFunction(int bankerCard, int playerCard);
int declareWinner(int winner, int decision, int bet);

int main() {
    srand(time(NULL)); // Initialize random number generator

    // Variable declaration
    string name;
    int bet, decision, winner, prize;
    char play;
    bool logic = true;
    int money = 10000;

    cout << "To Start, please enter your card" << endl;

    // Name input
    cout << "Enter your name: ";
    getline(cin, name);

    cout << "\nGood evening, " << name << endl;
    cout << "=================================\n";
    cout << "WELCOME TO VIRTUAL BACCARAT TABLE" << endl;
    cout << "=================================" << endl;

    do { // Main do-while loop
        cout << "Current balance, INR " << money << endl;
        cout << "1-BANKER \n2-PLAYER \n";
        cout << "Choose your bet: ";

        // Validate input for bet choice
        while (!(cin >> decision) || (decision < 1 || decision > 2)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid choice. Please choose again: ";
        }

        // Validate bet amount
        do {
            cout << "Place your bet, INR: ";
            cin >> bet;
        } while (bet > money || bet <= 0);

        // BANKER CARDS
        cout << "\n==============================\n";
        cout << "      - BANKER'S CARD -\n";
        cout << "==============================\n";

        Number banker;
        banker.num1 = rand() % 10 + 1;
        banker.num2 = rand() % 10 + 1;
        banker.sum = (banker.num1 + banker.num2) % 10;

        if (banker.sum != 9 && banker.sum != 8) {
            banker.extraCard = rand() % 10 + 1;
            banker.sum = (banker.sum + banker.extraCard) % 10;
            printCard1(banker.num1, banker.num2, banker.extraCard, banker.sum);
        } else {
            printCard2(banker.num1, banker.num2, banker.sum);
        }

        // PLAYER CARDS
        cout << "\n==============================\n";
        cout << "      - PLAYER'S CARD -\n";
        cout << "==============================\n";

        Number player;
        player.num1 = rand() % 10 + 1;
        player.num2 = rand() % 10 + 1;
        player.sum = (player.num1 + player.num2) % 10;

        if (player.sum != 9 && player.sum != 8) {
            player.extraCard = rand() % 10 + 1;
            player.sum = (player.sum + player.extraCard) % 10;
            printCard1(player.num1, player.num2, player.extraCard, player.sum);
        } else {
            printCard2(player.num1, player.num2, player.sum);
        }

        // Determine and declare winner
        winner = winnerFunction(banker.sum, player.sum);
        prize = declareWinner(winner, decision, bet);
        cout << "INR " << prize << endl;
        money += prize;
        cout << "Current Money, INR " << money << "\n\n";

        // Ask if the user wants to play again
        cout << "PLAY AGAIN? Y/N ";
        cin >> play;
        logic = playAgain(play, money);

    } while (logic);

    return 0;
}

void printCard1(int num1, int num2, int num3, int sum) {
    cout << "-------\n";
    cout << "|     |\n";
    cout << "|  " << sum << "  |\n";
    cout << "|     |\n";
    cout << "-------\n";
    cout << "First Card: " << num1 << "\n";
    cout << "Second Card: " << num2 << "\n";
    cout << "Extra Card: " << num3 << "\n";
}

void printCard2(int num1, int num2, int sum) {
    cout << "-------\n";
    cout << "|     |\n";
    cout << "|  " << sum << "  |\n";
    cout << "|     |\n";
    cout << "-------\n";
    cout << "This is a natural win 8/9\n";
    cout << "First Card: " << num1 << "\n";
    cout << "Second Card: " << num2 << "\n";
}

bool playAgain(char x, int money) {
    if (money > 0) {
        if (x == 'Y' || x == 'y') {
            return true;
        } else if (x == 'N' || x == 'n') {
            cout << "THANK YOU FOR PLAYING!" << endl;
            return false;
        }
    } else {
        cout << "Insufficient funds!" << endl;
        return false;
    }
    return false;
}

int winnerFunction(int bankerCard, int playerCard) {
    cout << "\n==================================\n";
    if (bankerCard > playerCard) {
        cout << "BANKER WINS!\n";
        return 1;
    } else if (bankerCard < playerCard) {
        cout << "PLAYER WINS!\n";
        return 2;
    } else {
        cout << "DRAW!\n";
        return 3;
    }
}

int declareWinner(int winner, int decision, int bet) {
    if (winner == decision) {
        cout << "YOU WIN!\n";
        return bet;
    } else if (winner == 3) {
        cout << "Tie Game!" << endl;
        return 0;
    } else {
        cout << "YOU LOSE!\n";
        return -bet;
    }
}
