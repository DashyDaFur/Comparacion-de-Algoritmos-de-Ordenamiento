#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>

// -- Valores configurables --
// NOTA: Recomiendo no cambiar el NUM_ALGORITMOS
#define NUM_ALGORITMOS 7
#define NUM_PRUEBAS 1000
#define MIN_TAM 10
#define MAX_TAM 1000
#define INCREMENTO 10
#define MIN_NUM 1
#define MAX_NUM 100

// Funcion para crear un valor aleatorio entre los rangos inicio y fin
inline double Aleatorio(int inicio, int fin);
// Entra el arreglo y lo ordena, regresando la duracion en nanosegundos
double ProcesarArreglo(std::vector<double>& a, int algoritmo);
// Exporta el arreglo a un archivo CSV
void ExportarCSV(const std::vector<std::vector<double>>& datos, const std::string& nombre);

// Metodos de ordenamiento
void OrdenarPorInsercion(std::vector<double>& s, int n);
void OrdenarBurbuja(std::vector<double>& s, int n);
void OrdenarSeleccion(std::vector<double>& s, int n);
void OrdenarMezcla(std::vector<double>& s, int inicio, int fin);
void Mezcla(std::vector<double>& s, int inicio, int medio, int fin);
void OrdenarRapido(std::vector<double>& s, int inicio, int fin);
int Particion(std::vector<double>& s, int inicio, int fin);
void OrdenarHeap(std::vector<double>& s, int n);
void Build_Max_Heap(std::vector<double>& s, int n);
void Max_Heapify(std::vector<double>& s, int i, int n);
void OrdenarShell(std::vector<double>& s, int n);

using namespace std;
using namespace std::chrono;

int main()
{
    // Inicia la semilla para números aleatorios
    srand(time(NULL));
    // Nombres de los algoritmos de ordenamiento
    string Nombres[NUM_ALGORITMOS] = {"Insercion", "Burbuja", "Seleccion", "Mezcla", "Rapido", "Heap", "Shell"};

    // Vector para almacenar tiempos: [algoritmo][tamaño][prueba]
    vector<vector<vector<double>>> tiempos(NUM_ALGORITMOS);

    // Prueba con diferentes tamaños de arreglos
    for (int tam = MIN_TAM; tam <= MAX_TAM; tam += INCREMENTO) {
        cout << "Size: " << tam << endl;

        // Genera arreglos aleatorios para las pruebas
        vector<vector<double>> arreglos(NUM_PRUEBAS, vector<double>(tam));
        for (int prueba = 0; prueba < NUM_PRUEBAS; prueba++) {
            for (int j = 0; j < tam; j++) {
                arreglos[prueba][j] = Aleatorio(MIN_NUM, MAX_NUM);
            }
        }

        // Ejecuta cada algoritmo de ordenamiento
        for (int algoritmo = 0; algoritmo < NUM_ALGORITMOS; algoritmo++) {
            vector<double> tiempos_tam;

            for (int prueba = 0; prueba < NUM_PRUEBAS; prueba++) {
                vector<double> copia = arreglos[prueba];

                double tiempo = ProcesarArreglo(copia, algoritmo);
                tiempos_tam.push_back(tiempo);
            }

            tiempos[algoritmo].push_back(tiempos_tam);
            cout << "  " << Nombres[algoritmo] << " Finished" << endl;
        }
    }
    // Exporta resultados a archivos CSV
    for (int algoritmo = 0; algoritmo < NUM_ALGORITMOS; algoritmo++) {
        ExportarCSV(tiempos[algoritmo], to_string(algoritmo + 1) + "_" + Nombres[algoritmo] + "_Ordenamiento.csv");
    }

    system("pause");
    return 0;
}

double ProcesarArreglo(std::vector<double>& a, int algoritmo)
{
    auto inicio = steady_clock::now();

    switch (algoritmo) {
        case 0: OrdenarPorInsercion(a,a.size()); break;
        case 1: OrdenarBurbuja(a,a.size()); break;
        case 2: OrdenarSeleccion(a,a.size()); break;
        case 3: OrdenarMezcla(a, 0, a.size() - 1); break;
        case 4: OrdenarRapido(a, 0, a.size() - 1); break;
        case 5: OrdenarHeap(a, a.size()); break;
        case 6: OrdenarShell(a, a.size()); break;
    }

    auto fin = steady_clock ::now();
    auto duracion = duration_cast<nanoseconds>(fin - inicio);

    return duracion.count();
}


inline double Aleatorio(int inicio, int fin)
{
    return inicio + rand() % (fin - inicio + 1);
}

void ExportarCSV(const std::vector<std::vector<double>>& datos, const std::string& nombre)
{
    ofstream archivo(nombre);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombre << endl;
        return;
    }

    for (int tam = MIN_TAM; tam <= MAX_TAM; tam += INCREMENTO) {
        archivo << "Size " << tam << ',';
    }
    archivo << endl;

    for (int i = 0; i < NUM_PRUEBAS; i++) {
        for (int j = 0; j < datos.size(); j++) {
            archivo << datos[j][i] << ',';
        }
        archivo << endl;
    }

    archivo.close();
}

void OrdenarPorInsercion(std::vector<double>& s, int n)
{
    for (int i = 1; i < n; i++) {
        double val = s[i];
        int j = i - 1;
        while (j >= 0 && val < s[j]) {
            s[j+1] = s[j];
            j--;
        }
        s[j+1] = val;
    }
}

void OrdenarBurbuja(std::vector<double>& s, int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j] > s[j + 1]) {
                double aux = s[j];
                s[j] = s[j + 1];
                s[j + 1] = aux;
            }
        }
    }
}

void OrdenarSeleccion(std::vector<double>& s, int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (s[j] < s[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            double temp = s[i];
            s[i] = s[min_idx];
            s[min_idx] = temp;
        }
    }
}

void OrdenarMezcla(std::vector<double>& s, int inicio, int fin)
{
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;
        OrdenarMezcla(s, inicio, medio);
        OrdenarMezcla(s, medio + 1, fin);
        Mezcla(s, inicio, medio, fin);
    }
}

void Mezcla(std::vector<double>& s, int inicio, int medio, int fin)
{
    int n1 = medio - inicio + 1, n2 = fin - medio;

    vector<double> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = s[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = s[medio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            s[k] = L[i];
            i++;
        } else {
            s[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        s[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        s[k] = R[j];
        j++;
        k++;
    }
}

void OrdenarRapido(std::vector<double>& s, int inicio, int fin)
{
    if (inicio < fin) {
        int pivote_idx = Particion(s, inicio, fin);
        OrdenarRapido(s, inicio, pivote_idx - 1);
        OrdenarRapido(s, pivote_idx + 1, fin);
    }
}

int Particion(std::vector<double>& s, int inicio, int fin)
{
    double pivote = s[fin];
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (s[j] <= pivote) {
            i++;
            swap(s[i], s[j]);
        }
    }

    swap(s[i + 1], s[fin]);
    return i + 1;
}

void OrdenarHeap(std::vector<double>& s, int n)
{
    Build_Max_Heap(s, n);
    for (int i = n - 1; i >= 1; i--) {
        swap(s[0], s[i]);
        Max_Heapify(s, 0, i);
    }
}

void Build_Max_Heap(std::vector<double>& s, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        Max_Heapify(s, i, n);
    }
}

void Max_Heapify(std::vector<double>& s, int i, int n)
{
    int izquierdo = 2 * i + 1, derecho = 2 * i + 2, mayor = i;

    if (izquierdo < n && s[izquierdo] > s[mayor]) {
        mayor = izquierdo;
    }
    if (derecho < n && s[derecho] > s[mayor]) {
        mayor = derecho;
    }
    if (mayor != i) {
        swap(s[i], s[mayor]);
        Max_Heapify(s, mayor, n);
    }
}

void OrdenarShell(std::vector<double>& s, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            double temp = s[i];
            int j = i;
            while (j >= gap && s[j - gap] > temp) {
                s[j] = s[j - gap];
                j -= gap;
            }
            s[j] = temp;
        }
    }
}
