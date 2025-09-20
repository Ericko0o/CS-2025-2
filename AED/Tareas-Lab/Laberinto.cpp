#include <iostream>
using namespace std;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

// m: puntero a la matriz (fila 0, col 0)
// visited: puntero a la matriz de visited (0 = no probado / 1 = dead-end)
bool buscarCamino(char* m, char* visited, int x, int y, int xf, int yf, int n) {
    int pos = x * n + y;       // posición lineal de (x,y)
    char* cur = m + pos;       // puntero a la celda actual

    // Si llegamos a B, devolvemos true (dejamos las marcas del camino)
    if (*cur == 'B') return true;

    // Marcar como parte del camino actual (visual, provisional)
    if (*cur != 'A') *cur = '+';

    // Explorar 4 direcciones
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        // Verificar límites
        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
            int pos2 = nx * n + ny;
            char* neigh = m + pos2;       // puntero al vecino
            char* vpos2 = visited + pos2; // puntero a visited[pos2]

            // Intentar recursión solo si el vecino es espacio o B
            // y además NO es un dead-end ya conocido
            if ((*neigh == ' ' || *neigh == 'B') && !(*vpos2)) {
                if (buscarCamino(m, visited, nx, ny, xf, yf, n))
                    return true; // si alguna rama encuentra B, propagamos true
            }
        }
    }

    // Si ninguna dirección funcionó -> retroceder:
    // 1) desmarcar la celda (restaurar a espacio, excepto si era 'A')
    if (*cur != 'A') *cur = ' ';
    // 2) marcar como dead-end para no reexplorarla desde otras ramas
    visited[pos] = 1;
    return false;
}

// Mostrar la matriz usando aritmética de punteros
void mostrar(char* m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << *(m + i * n + j) << " ";
        }
        cout << endl;
    }
}

int main() {
    char matriz[10][10] = {
        {'A','X',' ',' ',' ',' ',' ',' ',' ','X'},
        {' ','X',' ',' ',' ',' ','X','X',' ','X'},
        {' ','X',' ','X','X',' ','X','X','X','X'},
        {' ','X',' ','X',' ',' ','X',' ',' ',' '},
        {' ',' ',' ','X',' ',' ',' ',' ','X','X'},
        {' ','X','X','X','X','X',' ',' ','X',' '},
        {' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
        {' ','X','X',' ','X',' ',' ','X','X','X'},
        {'X','X',' ',' ','X',' ',' ','X',' ',' '},
        {' ',' ',' ','X','X',' ',' ',' ',' ','B'}
    };

    // visited inicializado a 0 (no probado)
    char visited[10][10] = { {0} };
    char* m = &matriz[0][0];
    char* v = &visited[0][0];

    int xi = 0, yi = 0;
    int xf = 9, yf = 9;

    if (buscarCamino(m, v, xi, yi, xf, yf, 10))
        cout << "Camino encontrado:\n";
    else
        cout << "No hay camino\n";

    mostrar(m, 10);
    return 0;
}
