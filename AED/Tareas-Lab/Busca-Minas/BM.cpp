#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void llenar(int (*mat)[10]) {
    int* p = &mat[0][0];
    for (int k = 0; k < 100; k++) {
        *(p + k) = 0;
    }
}

void ponerMinas(int (*mat)[10], int minas) {
    srand(time(0));
    int puestas = 0;
    while (puestas < minas) {
        int pos = rand() % 100;  // posición lineal de 0 a 99
        int* p = &mat[0][0] + pos;
        if (*p == 0) {
            *p = -1;
            puestas++;
        }
    }
}

void colocarNumeros(int (*mat)[10]) {
    int* base = &mat[0][0];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int* p = base + i * 10 + j;
            if (*p == -1) {
                for (int f = -1; f <= 1; f++) {
                    for (int g = -1; g <= 1; g++) {
                        int ni = i + f, nj = j + g;
                        if (ni >= 0 && ni < 10 && nj >= 0 && nj < 10) {
                            int* vecino = base + ni * 10 + nj;
                            if (*vecino != -1) (*vecino)++;
                        }
                    }
                }
            }
        }
    }
}

void mostrar(int (*mat)[10]) {
    int* p = &mat[0][0];
    for (int i = 0; i < 100; i++) {
        cout << *(p + i) << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
}

int main() {
    int arr[10][10];
    int minas, fila, col;

    cout << "Ingrese numero de minas (1-10): ";
    cin >> minas;

    llenar(arr);
    ponerMinas(arr, minas);
    colocarNumeros(arr);

    do {
        cout << "\nElija fila (0-9): ";
        cin >> fila;
        cout << "Elija columna (0-9): ";
        cin >> col;

        if (arr[fila][col] == -1) {
            cout << "💥 BOOM! Pisaste una mina!" << endl;
        } else {
            cout << "Seguro, valor: " << arr[fila][col] << endl;
        }

        cout << "\nTablero:" << endl;
        mostrar(arr);

    } while (arr[fila][col] != -1);

    return 0;
}
