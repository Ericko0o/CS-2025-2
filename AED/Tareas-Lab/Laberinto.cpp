#include <iostream>
using namespace std;

// Movimientos: arriba, abajo, izquierda, derecha
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

bool buscarCamino(char mat[10][10], int x, int y, int xf, int yf, int n) {
    char* fila = mat[x];
    if (*(fila + y) == 'B') return true;

    if (*(fila + y) != 'A')
        *(fila + y) = '+';

    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
            char* f2 = mat[nx];
            if (*(f2 + ny) == ' ' || *(f2 + ny) == 'B') {
                if (buscarCamino(mat, nx, ny, xf, yf, n))
                    return true;
            }
        }
    }

    if (*(fila + y) != 'A')
        *(fila + y) = ' ';

    return false;
}

void mostrar(char mat[10][10], int n) {
    for (int i = 0; i < n; i++) {
        char* fila = mat[i];
        for (int j = 0; j < n; j++) {
            cout << *(fila + j) << " ";
        }
        cout << endl;
    }
}

int main() {
    char matriz[10][10] = {
        {'A','X',' ',' ',' ',' ',' ',' ',' ','X'},
        {' ','X',' ',' ',' ',' ','X','X',' ','X'},
        {' ','X',' ','X','X',' ','X','X','X',' '},
        {' ','X',' ','X',' ',' ','X',' ',' ',' '},
        {' ',' ',' ','X',' ',' ',' ',' ','X',' '},
        {' ','X','X','X','X','X',' ','X','X',' '},
        {' ','X',' ',' ','X',' ',' ',' ','X',' '},
        {' ','X','X',' ','X','X','X',' ','X',' '},
        {' ',' ',' ',' ','X',' ','X',' ',' ',' '},
        {'X','X','X','X','X',' ','X','X','X','B'}
    };

    int xi = 0, yi = 0;
    int xf = 9, yf = 9;

    if (buscarCamino(matriz, xi, yi, xf, yf, 10))
        cout << "Camino encontrado:\n";
    else
        cout << "No hay camino\n";

    mostrar(matriz, 10);

    return 0;
}
