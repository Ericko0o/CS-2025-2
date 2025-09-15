#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
using namespace std;

void llenar(int (*mat)[10], int inicio, int fin) {
    int* base = &mat[0][0];
    for (int i = inicio; i < fin; i++) {
        for (int j = 0; j < 10; j++) {
            *(base + i * 10 + j) = 0;
        }
    }
}

void ponerMinas(int (*mat)[10], int minas) {
    srand(time(0));
    int puestas = 0;
    while (puestas < minas) {
        int fila = rand() % 10;
        int col  = rand() % 10;
        int* p = &mat[0][0] + fila * 10 + col;
        if (*p == 0) {
            *p = -1;
            puestas++;
        }
    }
}

void colocarNumeros(int (*mat)[10], int inicio, int fin) {
    int* base = &mat[0][0];
    for (int i = inicio; i < fin; i++) {
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
    int* base = &mat[0][0];
    for (int i = 0; i < 100; i++) {
        cout << *(base + i) << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
}

int main() {
    int arr[10][10];
    int minas, fila, col;

    cout << "Ingrese numero de minas: ";
    cin >> minas;

    // 4 hilos para llenar
    thread t1(llenar, arr, 0, 10/4);
    thread t2(llenar, arr, 10/4, 10/2);
    thread t3(llenar, arr, 10/2, 3*10/4);
    thread t4(llenar, arr, 3*10/4, 10);
    t1.join(); t2.join(); t3.join(); t4.join();

    ponerMinas(arr, minas);

    // 4 hilos para colocar números
    thread n1(colocarNumeros, arr, 0, 10/4);
    thread n2(colocarNumeros, arr, 10/4, 10/2);
    thread n3(colocarNumeros, arr, 10/2, 3*10/4);
    thread n4(colocarNumeros, arr, 3*10/4, 10);
    n1.join(); n2.join(); n3.join(); n4.join();

    do {
        cout << "\nElija fila (0-9): ";
        cin >> fila;
        cout << "Elija columna (0-9): ";
        cin >> col;

        if (arr[fila][col] == -1) {
            cout << "💥 BOOM! Mina encontrada!" << endl;
        } else {
            cout << "Valor seguro: " << arr[fila][col] << endl;
        }

        cout << "\nTablero:" << endl;
        mostrar(arr);

    } while (arr[fila][col] != -1);

    return 0;
}
