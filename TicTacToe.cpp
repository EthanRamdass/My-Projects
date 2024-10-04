#include <iostream>
using namespace std;

char board[3][3]; // 3x3 Tic Tac Toe board
char currentMarker;
char currentPlayer;

// Function to initialize the game board
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '1' + (i * 3 + j); // Filling the board with 1-9
        }
    }
}

// Function to print the game board
void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | "; // Print | between the columns
        }
        cout << "\n";
        if (i < 2) cout << "---------\n"; // Print line between the rows
    }
    cout << "\n";
}

// Function to place a marker on the board
bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    // Check if the slot is available
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentMarker;
        return true;
    } else {
        return false;
    }
}

// Function to check for a win
bool checkWin() {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;

    return false;
}

// Function to swap the player
void swapPlayer() {
    currentPlayer = (currentPlayer == '1') ? '2' : '1';
    currentMarker = (currentMarker == 'X') ? 'O' : 'X';
}

// Function to check if the board is full
bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') return false;
        }
    }
    return true;
}

int main() {
    cout << "Welcome to Tic Tac Toe!\n";
    initializeBoard();

    cout << "Player 1, choose your marker (X or O): ";
    cin >> currentMarker;

    currentPlayer = '1'; // Player 1 starts

    if (currentMarker == 'O') {
        currentMarker = 'X';
        swapPlayer();
    }

    int slot;
    bool gameOver = false;

    while (!gameOver) {
        printBoard();
        cout << "Player " << currentPlayer << "'s turn. Enter your slot (1-9): ";
        cin >> slot;

        if (slot < 1 || slot > 9 || !placeMarker(slot)) {
            cout << "Invalid slot. Try again.\n";
            continue;
        }

        if (checkWin()) {
            printBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        } else if (isBoardFull()) {
            printBoard();
            cout << "It's a tie!\n";
            gameOver = true;
        } else {
            swapPlayer();
        }
    }

    return 0;
}
