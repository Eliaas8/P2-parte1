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

// --- NUEVA FUNCION PARA MOSTRAR DATOS DE FORMA ORDENADA ---
// Recibe el vector y muestra 10 elementos por pagina
void mostrarProductosPaginado(const vector<Producto>& lista) {
    int total = lista.size();
    if (total == 0) {
        cout << "No hay productos para mostrar.\n";
        return;
    }

    char opcion = 's';
    int itemsPorPagina = 10;

    for (int i = 0; i < total; i += itemsPorPagina) {
        cout << "\n--- Mostrando productos " << i + 1 << " al " << min(i + itemsPorPagina, total) << " ---\n";
        cout << "ID\tNombre\t\tPrecio\t\tCalif\n"; // Encabezados simples
        cout << "--------------------------------------------------\n";

        // Bucle interno para mostrar solo el lote actual
        for (int j = i; j < i + itemsPorPagina && j < total; j++) {
            // Usamos getters del objeto. Asumo que getNombre() devuelve string corto, si es largo puede descuadrar
            cout << lista[j].getId() << "\t" 
                 << lista[j].getNombre() << "\t\t$" 
                 << lista[j].getPrecio() << "\t\t" 
                 << lista[j].getCalificacionPromedio() << "\n";
        }

        // Si quedan mas productos, preguntamos si quiere seguir
        if (i + itemsPorPagina < total) {
            cout << "\n¿Ver siguientes 10? (s/n): ";
            cin >> opcion;
            if (opcion == 'n' || opcion == 'N') break;
        } else {
            cout << "\n--- Fin de la lista ---\n";
        }
    }
}

// MENÚ VISUAL
void menuVisual() {
    cout << "\n========= MENU PRINCIPAL =========\n";
    cout << "1. Generar 50 Productos\n";
    cout << "2. Comparar Algoritmos (Sort) y Ver Lista\n";
    cout << "3. Busqueda Binaria (Buscar ID especifico)\n";
    cout << "4. Medir tiempos de busqueda (Test Masivo)\n";
    cout << "5. Salir\n";
    cout << "===================================\n";
    cout << "Ingrese una opcion: ";
}

int main() {
    srand(time(0));
    
    vector<Producto> listaProductos; 
    int opcion = 0;

    // Datos para generacion aleatoria
    const string categorias[] = {"Electrónica", "Ropa", "Libros", "Hogar", "Deportes"};
    const int cantidadDeCategorias = 5;
    const string nombres[] = {"Smartphone", "Camiseta", "Sofá", "Novela", "Laptop", "Pantalones", "Reloj", "Mesa", "Auriculares", "Zapatos"};
    const int cantidadDeNombres = 10;

    do {
        menuVisual();
        if (!(cin >> opcion)) { 
            cout << "Entrada invalida.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch(opcion) {
            case 1: { 
                cout << "--- Generando 50 Productos ---\n";
                listaProductos.clear(); 
                
                for (int i = 0; i < 50; i++) {
                    int id = i + 1;
                    string nombre = nombres[rand() % cantidadDeNombres];
                    string categoria = categorias[rand() % cantidadDeCategorias];
                    float precio = (float)(rand() % 991) + 10; 
                    int stock = rand() % 101;                  
                    float calif = (rand() % 401 + 100) / 100.0f;

                    Producto p(id, nombre, precio, categoria, stock, calif);
                    listaProductos.push_back(p);
                }
                cout << "Productos generados exitosamente.\n";

                // Preguntamos si quiere ver la lista generada
                char verLista;
                cout << "¿Desea ver la lista generada? (s/n): ";
                cin >> verLista;
                if (verLista == 's' || verLista == 'S') {
                    mostrarProductosPaginado(listaProductos);
                }
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

                vector<Producto> vecInsert = listaProductos;
                vector<Producto> vecQuick = listaProductos;
                vector<Producto> vecMerge = listaProductos;

                if (subOpcion == 1) {
                    cout << "\n--- Midiendo Tiempos de Ordenamiento (Precio Ascendente) ---\n";
                    
                    auto start = high_resolution_clock::now();
                    insertionSort(vecInsert, precioAsc);
                    auto stop = high_resolution_clock::now();
                    cout << "Insertion Sort: " << duration_cast<microseconds>(stop - start).count() << " microsegundos.\n";

                    start = high_resolution_clock::now();
                    runQuickSort(vecQuick, precioAsc);
                    stop = high_resolution_clock::now();
                    cout << "Quick Sort:     " << duration_cast<microseconds>(stop - start).count() << " microsegundos.\n";

                    start = high_resolution_clock::now();
                    runMergeSort(vecMerge, precioAsc);
                    stop = high_resolution_clock::now();
                    cout << "Merge Sort:     " << duration_cast<microseconds>(stop - start).count() << " microsegundos.\n";

                    listaProductos = vecQuick; // Actualizamos la lista principal
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

                    listaProductos = vecQuick; // Actualizamos la lista principal
                }

                // Preguntamos si quiere ver la lista ya ordenada
                char verLista;
                cout << "¿Desea ver la lista ordenada? (s/n): ";
                cin >> verLista;
                if (verLista == 's' || verLista == 'S') {
                    mostrarProductosPaginado(listaProductos);
                }
                break;
            }

            case 3: { // Busqueda manual
                if (listaProductos.empty()) {
                    cout << "Error: Lista vacia.\n";
                    break;
                }
                
                runQuickSort(listaProductos, idAsc); // Ordenar por ID es obligatorio para busqueda binaria

                int targetID;
                cout << "Ingrese ID a buscar: ";
                cin >> targetID;

                int index = binarySearch(listaProductos, targetID);
                if (index != -1) {
                    Producto p = listaProductos[index];
                    cout << "\n--- Producto Encontrado ---\n";
                    cout << "ID: " << p.getId() << " | " << p.getNombre() << " | $" << p.getPrecio() << "\n";
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
                runQuickSort(listaProductos, idAsc);

                auto startSearch = high_resolution_clock::now();
                int encontrados = 0, noEncontrados = 0;

                for(int i=0; i<10; i++) {
                    int target = (rand() % 50) + 1;
                    if(binarySearch(listaProductos, target) != -1) encontrados++;
                }
                for(int i=0; i<10; i++) {
                    int target = (rand() % 50) + 100;
                    if(binarySearch(listaProductos, target) == -1) noEncontrados++;
                }
                
                auto stopSearch = high_resolution_clock::now();
                auto durationSearch = duration_cast<nanoseconds>(stopSearch - startSearch);

                cout << "Tiempo total (20 busquedas): " << durationSearch.count() << " nanosegundos.\n";
                cout << "Exito: " << encontrados << "/10 existentes, " << noEncontrados << "/10 no existentes.\n";
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
