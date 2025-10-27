
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
    resetBoard();
    currentPlayer = 'X';
    bool gameOver = false;

    while (!gameOver) {
        printBoard();
        int pos;

        cout << "Jugador " << currentPlayer << ", elige una posición (1-9): ";
        cin >> pos;

        // ✅ Validación de entrada
        if (cin.fail() || pos < 1 || pos > 9 || board[pos - 1] == 'X' || board[pos - 1] == 'O') {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "❌ Movimiento no válido. Intenta de nuevo.\n";
            continue;
        }

        board[pos - 1] = currentPlayer;

        if (checkWin()) {
            printBoard();
            cout << "🎉 ¡Jugador " << currentPlayer << " ha ganado!\n";
            gameOver = true;
        } else if (checkDraw()) {
            printBoard();
            cout << "🤝 ¡Es un empate!\n";
            gameOver = true;
        } else {
            switchPlayer();
        }
    }

    cout << "👋 ¡Gracias por jugar!\n";
    return 0;
}


