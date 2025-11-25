#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime>   
#include <chrono>  // Para medir tiempo con precision
#include "Producto.h"
#include "Algoritmos.h" // Incluimos nuestros algoritmos

using namespace std;
using namespace std::chrono;

// Funciones de comparacion para los sorts
bool precioAsc(const Producto& a, const Producto& b) { return a.getPrecio() < b.getPrecio(); }
bool califDesc(const Producto& a, const Producto& b) { return a.getCalificacionPromedio() > b.getCalificacionPromedio(); }
bool idAsc(const Producto& a, const Producto& b) { return a.getId() < b.getId(); }

// MENÚ VISUAL
void menuVisual() {
    cout << "\n========= MENU PRINCIPAL =========\n";
    cout << "1. Generar 50 Productos\n";
    cout << "2. Ordenar Productos\n";
    cout << "3. Busqueda Binaria por ID\n";
    cout << "4. Medir tiempos de busqueda\n";
    cout << "5. Salir\n";
    cout << "===================================\n";

    cout << "\n------ ORDENAMIENTO ------\n";
    cout << "1. Precio (Ascendente)\n";
    cout << "2. Calificacion (Descendente)\n";
    cout << "----------------------------------\n";

    cout << "\n--- Algoritmos Disponibles ---\n";
    cout << "1. Insertion Sort\n";
    cout << "2. Quick Sort\n";
    cout << "3. Merge Sort\n";
    cout << "---------------------------------\n";
}

int main() {
    srand(time(0));
    
    menuVisual();
    
    vector<Producto> listaProductos;

    // Datos para generacion aleatoria
    const string categorias[] = {"Electrónica", "Ropa", "Libros", "Hogar", "Deportes"};
    const int cantidadDeCategorias = 5;

    const string nombres[] = {"Smartphone", "Camiseta", "Sofá", "Novela", "Laptop", "Pantalones", "Reloj", "Mesa", "Auriculares", "Zapatos"};
    const int cantidadDeNombres = 10;

    cout << "--- Generando 50 Productos ---\n";
    for (int i = 0; i < 50; i++) {
        int id = i + 1;
        
        // Seleccion aleatoria de arrays predefinidos
        string nombre = nombres[rand() % cantidadDeNombres];
        string categoria = categorias[rand() % cantidadDeCategorias];
        
        // (rand() % (max-min+1)) + min
        float precio = (float)(rand() % 991) + 10; // 10 a 1000
        int stock = rand() % 101;                  // 0 a 100
        
        // Genera 100 a 500, divide por 100.0 para obtener 1.0 a 5.0
        float calif = (rand() % 401 + 100) / 100.0f;

        Producto p(id, nombre, precio, categoria, stock, calif);
        listaProductos.push_back(p);
    }
    
    // Copiamos vectores para que cada algoritmo ordene los mismos datos desordenados
    vector<Producto> vecInsert = listaProductos;
    vector<Producto> vecQuick = listaProductos;
    vector<Producto> vecMerge = listaProductos;

    cout << "\n--- Midiendo Tiempos de Ordenamiento (Precio Ascendente) ---\n";
    
    // 1. Insertion Sort
    auto start = high_resolution_clock::now();
    insertionSort(vecInsert, precioAsc);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Insertion Sort: " << duration.count() << " microsegundos.\n";

    // 2. Quick Sort
    start = high_resolution_clock::now();
    runQuickSort(vecQuick, precioAsc);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Quick Sort:     " << duration.count() << " microsegundos.\n";

    // 3. Merge Sort
    start = high_resolution_clock::now();
    runMergeSort(vecMerge, precioAsc);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Merge Sort:     " << duration.count() << " microsegundos.\n";

    // Mostramos el primero y ultimo del vector ordenado (Quick) para verificar
    cout << "Mas barato: " << vecQuick.front().getPrecio() << " | Mas caro: " << vecQuick.back().getPrecio() << "\n";


    cout << "\n--- Midiendo Tiempos de Ordenamiento (Calif Descendente) ---\n";
    // Reiniciamos vectores desordenados
    vecInsert = listaProductos;
    vecQuick = listaProductos;
    
    start = high_resolution_clock::now();
    insertionSort(vecInsert, califDesc);
    stop = high_resolution_clock::now();
    cout << "Insertion Sort: " << duration_cast<microseconds>(stop - start).count() << " microsegundos.\n";

    start = high_resolution_clock::now();
    runQuickSort(vecQuick, califDesc);
    stop = high_resolution_clock::now();
    cout << "Quick Sort:     " << duration_cast<microseconds>(stop - start).count() << " microsegundos.\n";

    cout << "Mejor Calif: " << vecQuick.front().getCalificacionPromedio() << " | Peor Calif: " << vecQuick.back().getCalificacionPromedio() << "\n";

    cout << "\n--- Parte 3: Busqueda Binaria por ID ---\n";
    
    // Primero ordenamos por ID (Requisito para busqueda binaria)
    runQuickSort(listaProductos, idAsc);

    auto startSearch = high_resolution_clock::now();
    int encontrados = 0;
    int noEncontrados = 0;

    // 10 busquedas existentes (IDs 1-50 existen)
    for(int i=0; i<10; i++) {
        int target = (rand() % 50) + 1;
        if(binarySearch(listaProductos, target) != -1) encontrados++;
    }

    // 10 busquedas NO existentes (IDs > 50)
    for(int i=0; i<10; i++) {
        int target = (rand() % 50) + 100;
        if(binarySearch(listaProductos, target) == -1) noEncontrados++;
    }
    
    auto stopSearch = high_resolution_clock::now();
    auto durationSearch = duration_cast<nanoseconds>(stopSearch - startSearch); // Nano porque es muy rapido

    cout << "Tiempo total (20 busquedas): " << durationSearch.count() << " nanosegundos.\n";
    cout << "Exito: Encontrados " << encontrados << "/10 existentes, Confirmados " << noEncontrados << "/10 no existentes.\n";

    return 0;
}
