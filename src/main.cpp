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
    cout << "2. Comparar Algoritmos (Sort)\n";
    cout << "3. Busqueda Binaria (Buscar ID especifico)\n";
    cout << "4. Medir tiempos de busqueda (Test Masivo)\n";
    cout << "5. Salir\n";
    cout << "===================================\n";
    cout << "Ingrese una opcion: ";
}

int main() {
    srand(time(0));
    
    vector<Producto> listaProductos; // El vector debe vivir fuera del bucle para persistir datos
    int opcion = 0;

    // Datos para generacion aleatoria (Moverlos fuera del switch evita re-declaracion constante)
    const string categorias[] = {"Electrónica", "Ropa", "Libros", "Hogar", "Deportes"};
    const int cantidadDeCategorias = 5;
    const string nombres[] = {"Smartphone", "Camiseta", "Sofá", "Novela", "Laptop", "Pantalones", "Reloj", "Mesa", "Auriculares", "Zapatos"};
    const int cantidadDeNombres = 10;

    do {
        menuVisual();
        if (!(cin >> opcion)) { 
            // Limpieza del buffer si el usuario ingresa texto en lugar de numeros
            cout << "Entrada invalida.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch(opcion) {
            case 1: { 
                cout << "--- Generando 50 Productos ---\n";
                listaProductos.clear(); // Limpiamos para no acumular infinitamente si se presiona 1 varias veces
                
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
                cout << "Productos generados exitosamente.\n";
                break;
            }

            case 2: {
                if (listaProductos.empty()) {
                    cout << "Error: La lista esta vacia. Genere productos primero (Opcion 1).\n";
                    break;
                }

                int subOpcion;
                cout << "\nCriterio: 1. Precio (Asc) | 2. Calif (Desc): ";
                cin >> subOpcion;

                // Copiamos vectores para que cada algoritmo ordene los mismos datos desordenados
                vector<Producto> vecInsert = listaProductos;
                vector<Producto> vecQuick = listaProductos;
                vector<Producto> vecMerge = listaProductos;

                if (subOpcion == 1) {
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
                    
                    // Actualizamos la lista principal para que quede ordenada
                    listaProductos = vecQuick;
                } 
                else if (subOpcion == 2) {
                    cout << "\n--- Midiendo Tiempos de Ordenamiento (Calif Descendente) ---\n";
                    
                    auto start = high_resolution_clock::now();
                    insertionSort(vecInsert, califDesc);
                    auto stop = high_resolution_clock::now();
                    cout << "Insertion Sort: " << duration_cast<microseconds>(stop - start).count() << " microsegundos.\n";

                    start = high_resolution_clock::now();
                    runQuickSort(vecQuick, califDesc);
                    stop = high_resolution_clock::now();
                    cout << "Quick Sort:     " << duration_cast<microseconds>(stop - start).count() << " microsegundos.\n";

                    cout << "Mejor Calif: " << vecQuick.front().getCalificacionPromedio() << " | Peor Calif: " << vecQuick.back().getCalificacionPromedio() << "\n";
                    
                    // Actualizamos la lista principal
                    listaProductos = vecQuick;
                }
                break;
            }

            case 3: { // Busqueda manual
                if (listaProductos.empty()) {
                    cout << "Error: Lista vacia.\n";
                    break;
                }
                
                // Primero ordenamos por ID (Requisito para busqueda binaria)
                runQuickSort(listaProductos, idAsc);

                int targetID;
                cout << "Ingrese ID a buscar: ";
                cin >> targetID;

                int index = binarySearch(listaProductos, targetID);
                if (index != -1) {
                    cout << "Producto encontrado: " << listaProductos[index].getNombre() << "\n";
                } else {
                    cout << "Producto no encontrado.\n";
                }
                break;
            }

            case 4: {
                if (listaProductos.empty()) {
                    cout << "Error: Lista vacia.\n";
                    break;
                }

                cout << "\n--- Parte 3: Busqueda Binaria por ID (Test Masivo) ---\n";
                
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
                break;
            }

            case 5:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 5);

    return 0;
}
