
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Imprime el tablero
void printBoard(const vector<vector<char>>& board) {
    cout << "\n";
    cout << "   1   2   3\n";
    for (int i = 0; i < 3; ++i) {
        cout << i+1 << "  ";
        for (int j = 0; j < 3; ++j) {
            cout << (board[i][j] == ' ' ? ' ' : board[i][j]);
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "  ---+---+---\n";
    }
    cout << "\n";
}

// Comprueba si hay ganador. Devuelve 'X' o 'O' si hay ganador, 'D' si empate, ' ' si continuar.
char checkWin(const vector<vector<char>>& b) {
    // Filas y columnas
    for (int i = 0; i < 3; ++i) {
        if (b[i][0] != ' ' && b[i][0] == b[i][1] && b[i][1] == b[i][2]) return b[i][0];
        if (b[0][i] != ' ' && b[0][i] == b[1][i] && b[1][i] == b[2][i]) return b[0][i];
    }
    // Diagonales
    if (b[0][0] != ' ' && b[0][0] == b[1][1] && b[1][1] == b[2][2]) return b[0][0];
    if (b[0][2] != ' ' && b[0][2] == b[1][1] && b[1][1] == b[2][0]) return b[0][2];

    // ¿Quedan casillas vacías?
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (b[i][j] == ' ') return ' ';

    // Empate
    return 'D';
}

// Pide y valida la jugada. Devuelve true si fue válida y colocó la marca.
bool makeMove(vector<vector<char>>& board, char player) {
    int row, col;
    cout << "Turno de " << player << ". Ingresa fila y columna (ej: 2 3): ";
    if (!(cin >> row >> col)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Por favor ingresa dos números entre 1 y 3.\n";
        return false;
    }
    if (row < 1 || row > 3 || col < 1 || col > 3) {
        cout << "Coordenadas fuera de rango. Usa valores entre 1 y 3.\n";
        return false;
    }
    if (board[row-1][col-1] != ' ') {
        cout << "Casilla ocupada. Elige otra.\n";
        return false;
    }
    board[row-1][col-1] = player;
    return true;
}

int main() {
    cout << "=== Tic Tac Toe ===\n";
    bool playAgain = true;
    while (playAgain) {
        vector<vector<char>> board(3, vector<char>(3, ' '));
        char current = 'X';
        char result = ' ';
        printBoard(board);

        while (true) {
            while (!makeMove(board, current)) { }
            printBoard(board);
            result = checkWin(board);
            if (result == 'X' || result == 'O') {
                cout << "¡Jugador " << result << " gana!\n";
                break;
            } else if (result == 'D') {
                cout << "Es un empate.\n";
                break;
            }
            current = (current == 'X') ? 'O' : 'X';
        }

        char resp;
        cout << "¿Jugar otra vez? (s/n): ";
        cin >> resp;
        if (resp != 's' && resp != 'S') playAgain = false;
    }
    cout << "Gracias por jugar. ¡Adiós!\n";
    return 0;
}
