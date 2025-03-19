# 🦊 Comparación de Algoritmos de Ordenamiento

Este proyecto compara el rendimiento de varios algoritmos de ordenamiento en términos de tiempo de ejecución.

Los algoritmos incluidos son:
1. **Ordenamiento por Inserción (Insertion Sort)**
2. **Ordenamiento de Burbuja (Bubble Sort)**
3. **Ordenamiento por Selección (Selection Sort)**
4. **Ordenamiento por Mezcla (Merge Sort)**
5. **Ordenamiento Rápido (Quick Sort)**
6. **Ordenamiento por Montículos (Heap Sort)**
7. **Ordenamiento de Shell (Shell Sort)**

El proyecto genera datos aleatorios y mide en nanosegundos el tiempo que tarda cada algoritmo en ordenar arreglos de diferentes tamaños. Los resultados se exportan en archivos CSV.

## 📋 Requisitos

- **g++ Compiler**
- **CMake** (opcional)

## 🔽 Compilación y Ejecución

### Compilación Manual

1. Clona el repositorio:
   ```bash
   git clone https://github.com/DashyDaFur/comparacion-de-algoritmos-de-ordenamiento.git
   cd comparacion-de-algoritmos-de-ordenamiento
   ```
2. Compila el código:
   ```bash
   g++ -o ordenamiento main.cpp -std=c++11
   ```
3. Ejecuta el programa:
   ```bash
   ./ordenamiento
   ```

### Uso de CMake

1. Clona el repositorio:
   ```bash
   git clone https://github.com/DashyDaFur/comparacion-de-algoritmos-de-ordenamiento.git
   cd comparacion-de-algoritmos-de-ordenamiento
   ```
2. Crea un directorio de compilación y compila el proyecto:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Ejecuta el programa:
   ```bash
   ./ordenamiento
   ```

## 🌳 Estructura del Proyecto

- **`main.cpp`**: Contiene el código principal que genera los datos, ejecuta los algoritmos de ordenamiento y exporta los resultados.
- **`README.md`**: Contiene una descripción general del proyecto.
- **Archivos CSV**: Los archivos CSV generados se guardan en el directorio raíz del proyecto.

## 🛠️ Configuración

Puedes modificar las siguientes constantes en el código para ajustar el programa:

- `NUM_ALGORITMOS`: Número de algoritmos de ordenamiento que se probarán.
- `NUM_PRUEBAS`: Número de pruebas que se realizarán para cada tamaño de arreglo.
- `MIN_TAM`: Tamaño mínimo del arreglo.
- `MAX_TAM`: Tamaño máximo del arreglo.
- `INCREMENTO`: Incremento en el tamaño del arreglo entre las pruebas.
- `MIN_NUM`: Valor mínimo de los números aleatorios generados.
- `MAX_NUM`: Valor máximo de los números aleatorios generados.

## ✅ Resultados

Los resultados se exportan a archivos CSV en el directorio raíz del proyecto. Cada archivo CSV contiene los tiempos de ejecución en nanosegundos para cada tamaño de arreglo y cada prueba.
