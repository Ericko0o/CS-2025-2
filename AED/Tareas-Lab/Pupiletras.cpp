#include <iostream>
#include <cstring> // Para strlen
using namespace std;

// Función que busca cuántas veces aparece la palabra
int buscarPalabra(char* p, const char* palabra, int filas, int cols) {
    int len = strlen(palabra); // Longitud de la palabra
    int contador = 0;
    if (len == 0) return 0;

    // Recorrer toda la matriz
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            // Apuntador a la posición inicial [i][j]
            char* inicio = p + i * cols + j;

            // ---- HORIZONTAL DERECHA (→) ----
            if (j + len <= cols) {
                bool ok = true;
                for (int k = 0; k < len; k++) {
                    if (*(inicio + k) != palabra[k]) { ok = false; break; }
                }
                if (ok) contador++;
            }

            // ---- HORIZONTAL IZQUIERDA (←) ----
            if (j - len + 1 >= 0) {
                bool ok = true;
                for (int k = 0; k < len; k++) {
                    if (*(inicio - k) != palabra[k]) { ok = false; break; }
                }
                if (ok) contador++;
            }

            // ---- VERTICAL ABAJO (↓) ----
            if (i + len <= filas) {
                bool ok = true;
                for (int k = 0; k < len; k++) {
                    if (*(inicio + k * cols) != palabra[k]) { ok = false; break; }
                }
                if (ok) contador++;
            }

            // ---- VERTICAL ARRIBA (↑) ----
            if (i - len + 1 >= 0) {
                bool ok = true;
                for (int k = 0; k < len; k++) {
                    if (*(inicio - k * cols) != palabra[k]) { ok = false; break; }
                }
                if (ok) contador++;
            }
        }
    }
    return contador;
}

int main() {
    // Matriz pupiletras (10x10)
    char matriz[10][10] = {
        {'T','P','P','A','P','T','P','I','P','T'},
        {'O','P','A','T','A','P','O','Z','O','J'},
        {'S','A','T','A','T','O','T','A','Z','I'},
        {'A','T','A','P','A','P','A','T','O','S'},
        {'P','A','T','A','N','O','P','O','T','N'},
        {'T','A','A','P','A','T','I','P','A','P'},
        {'R','R','N','A','D','O','T','A','D','O'},
        {'E','D','N','T','A','P','O','T','A','T'},
        {'N','I','I','A','T','I','T','A','P','A'},
        {'P','S','S','N','T','T','T','P','A','P'}
    };

    // Palabra a buscar
    char palabra[20];
    cout << "Ingrese la palabra a buscar: ";
    cin >> palabra;

    // Puntero al inicio de la matriz
    char* p = &matriz[0][0];

    // Buscar cuántas veces aparece
    int repeticiones = buscarPalabra(p, palabra, 10, 10);

    cout << "La palabra '" << palabra << "' aparece " 
         << repeticiones << " veces." << endl;

    return 0;
}
