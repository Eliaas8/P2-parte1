#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // numeros aleatorios
#include <ctime>   
#include <chrono> // mMdicion de tiempo
#include <iomanip> // permite crear columnas de ancho fijo y alinear texto con setw
#include "Producto.h"
#include "Algoritmos.h" 

using namespace std;
using namespace std::chrono;

// Funciones de comparacion (Predicados)
// Se usan para inyectar la logica de comparacion en los algoritmos genericos sin reescribirlos
bool precioAsc(const Producto& a, const Producto& b) { return a.getPrecio() < b.getPrecio(); }
bool califDesc(const Producto& a, const Producto& b) { return a.getCalificacionPromedio() > b.getCalificacionPromedio(); }
bool idAsc(const Producto& a, const Producto& b) { return a.getId() < b.getId(); }

// Visualizacion tabular controlada
void mostrarProductosPaginado(const vector<Producto>& lista) {
    int total = lista.size();
    if (total == 0) {
        cout << "No hay productos para mostrar.\n";
        return;
    }

    char opcion = 's';
    int itemsPorPagina = 10;

    for (int i = 0; i < total; i += itemsPorPagina) {
        cout << "\n--- Pagina " << (i/itemsPorPagina) + 1 << " ---\n";
        
        // Configuracion de la tabla:
        // 'left': Alinea el texto a la izquierda (mas legible para lectura humana).
        // 'setw(n)': Reserva n espacios estrictos. Si el dato es menor, rellena con espacios; si es mayor, no rompe la tabla.
        cout << left 
             << setw(6)  << "ID" 
             << setw(25) << "Nombre"          
             << setw(15) << "Categoria" 
             << setw(12) << "Precio"          
             << setw(8)  << "Stock" 
             << setw(8)  << "Calif" << endl;
        
        cout << string(75, '-') << endl; 

        // Imprime solo el segmento actual (i hasta i+10)
        for (int j = i; j < i + itemsPorPagina && j < total; j++) {
            cout << left 
                 << setw(6)  << lista[j].getId() 
                 << setw(25) << lista[j].getNombre() 
                 << setw(15) << lista[j].getCategoria();

            // Formato de moneda manual:
            // Imprimimos '$' y reducimos el setw del numero para mantener la alineacion perfecta
            cout << "$" << fixed << setprecision(2) << setw(11) << lista[j].getPrecio() 
                 << setw(8)  << lista[j].getStock() 
                 << setprecision(1) << lista[j].getCalificacionPromedio() << endl;
        }

        // Pausa la ejecucion para que el usuario pueda leer antes de hacer scroll
        if (i + itemsPorPagina < total) {
            cout << "\nVer mas? (s/n): ";
            cin >> opcion;
            if (opcion == 'n' || opcion == 'N') break;
        }
    }
}

void menuVisual() {
    cout << "\n========= GESTION TIENDA =========\n";
    cout << "1. Generar Datos (Parte 1)\n";
    cout << "2. Ordenar y Medir (Parte 2)\n";
    cout << "3. Busqueda Binaria ID (Parte 3)\n";
    cout << "4. Busqueda Lineal Nombre (Parte 3 - Opcional)\n";
    cout << "5. Salir\n";
    cout << "Opcion: ";
}

int main() {
    srand(time(0));
    vector<Producto> listaProductos; 
    int opcion = 0;

    // Arrays para generacion combinatoria (Sustantivo + Adjetivo)
    // Esto garantiza variedad y evita nombres duplicados frecuentes en la muestra de 50
    const string categorias[] = {"Electronica", "Ropa", "Libros", "Hogar", "Deportes"};
    const string sustantivos[] = {"Smartphone", "Camiseta", "Sofa", "Novela", "Laptop", "Pantalon", "Reloj", "Mesa", "Audifonos", "Zapatillas"};
    const string adjetivos[] = {"Pro", "Slim", "Confort", "Gamer", "Ultra", "Basico", "X", "Plus", "Air", "Max"};

    do {
        menuVisual();
        // Validacion de entrada para evitar bucles infinitos si se ingresa una letra
        if (!(cin >> opcion)) { 
            cin.clear(); cin.ignore(10000, '\n'); continue;
        }

        switch(opcion) {
            case 1: { 
                listaProductos.clear(); // Limpiamos para evitar duplicar la lista si se regenera
                cout << "--- Generando Catalogo ---\n";
                
                for (int i = 0; i < 50; i++) {
                    int id = i + 1; 
                    
                    // Combinatoria aleatoria para nombre realista
                    string nombre = sustantivos[rand() % 10] + " " + adjetivos[rand() % 10];
                    string categoria = categorias[rand() % 5];
                    
                    float precio = (float)(rand() % 991) + 10; 
                    int stock = rand() % 101;                  
                    float calif = (rand() % 401 + 100) / 100.0f; // Division flotante para obtener decimales (1.0 - 5.0)

                    listaProductos.push_back(Producto(id, nombre, precio, categoria, stock, calif));
                }
                cout << "50 Productos generados.\n";
                mostrarProductosPaginado(listaProductos);
                break;
            }

            case 2: {
                if (listaProductos.empty()) { cout << "Primero genere datos (Op 1).\n"; break; }
                
                int sub;
                cout << "1. Precio (Asc) | 2. Calif (Desc): "; cin >> sub;
                
                // Creamos copias independientes del vector original desordenado.
                // Es CRITICO para que la medicion de tiempos sea justa (todos ordenan lo mismo).
                vector<Producto> vQuick = listaProductos;
                vector<Producto> vMerge = listaProductos;
                vector<Producto> vInsert = listaProductos;
                
                // Seleccionamos la funcion de comparacion adecuada
                auto comp = (sub == 1) ? precioAsc : califDesc;

                cout << "\n--- Resultados de Rendimiento ---\n";
                
                // Medicion Insertion Sort
                auto t1 = high_resolution_clock::now();
                insertionSort(vInsert, comp);
                auto t2 = high_resolution_clock::now();
                cout << "Insertion Sort: " << duration_cast<microseconds>(t2-t1).count() << " us\n";

                // Medicion Quick Sort
                t1 = high_resolution_clock::now();
                runQuickSort(vQuick, comp);
                t2 = high_resolution_clock::now();
                cout << "Quick Sort:     " << duration_cast<microseconds>(t2-t1).count() << " us\n";

                // Medicion Merge Sort
                t1 = high_resolution_clock::now();
                runMergeSort(vMerge, comp);
                t2 = high_resolution_clock::now();
                cout << "Merge Sort:     " << duration_cast<microseconds>(t2-t1).count() << " us\n";

                // Actualizamos la lista principal con la version ordenada para visualizacion
                listaProductos = vQuick; 
                
                cout << "¿Ver lista ordenada? (s/n): ";
                char c; cin >> c;
                if(c=='s' || c=='S') mostrarProductosPaginado(listaProductos);
                break;
            }

            case 3: { // BUSQUEDA BINARIA
                if (listaProductos.empty()) { cout << "Vacia.\n"; break; }
                
                // REQUISITO OBLIGATORIO: La busqueda binaria SOLO funciona en datos ordenados por la clave de busqueda
                runQuickSort(listaProductos, idAsc); 
                
                int hits = 0, miss = 0;
                auto start = high_resolution_clock::now();
                
                // Simulacion de carga real: 10 exitosas y 10 fallidas
                for(int i=0; i<10; i++) if(binarySearch(listaProductos, (rand()%50)+1) != -1) hits++;
                for(int i=0; i<10; i++) if(binarySearch(listaProductos, (rand()%50)+100) == -1) miss++;
                
                auto stop = high_resolution_clock::now();
                
                // Usamos nanosegundos porque BinarySearch es extremadamente rapido en arrays pequeños
                cout << "Tiempo Binary Search (20 ops): " << duration_cast<nanoseconds>(stop - start).count() << " ns\n";
                cout << "Control: " << hits << " encontrados, " << miss << " no encontrados.\n";
                break;
            }

            case 4: { // BUSQUEDA LINEAL (Texto)
                if (listaProductos.empty()) { cout << "Vacia.\n"; break; }
                
                string query;
                cout << "Ingrese texto a buscar (ej: 'Gamer'): ";
                cin >> query;

                auto start = high_resolution_clock::now();
                vector<int> indices = linearSearchSubstr(listaProductos, query);
                auto stop = high_resolution_clock::now();

                if(indices.empty()) {
                    cout << "No se encontraron coincidencias.\n";
                } else {
                    cout << "Encontrados " << indices.size() << " productos en " 
                         << duration_cast<microseconds>(stop - start).count() << " us:\n";
                    for(int idx : indices) {
                        cout << "- " << listaProductos[idx].getNombre() << " ($" << listaProductos[idx].getPrecio() << ")\n";
                    }
                }
                break;
            }
            case 5: cout << "Saliendo...\n"; break;
        }
    } while (opcion != 5);
    return 0;
}
