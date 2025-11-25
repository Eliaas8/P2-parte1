#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

// [EDUARDO - TODO #20] Incluye el header "Producto.h" para poder crear objetos.
#include "Producto.h"

using namespace std;

int main() {
    // [FEDE - TODO #21] Inicializa la semilla aleatoria usando srand(time(0)).
    // Esto asegura que obtengamos números diferentes cada vez que corramos el programa.
    srand(time(0));

    // [EDUARDO - TODO #22] Crea un vector (o arreglo) para guardar los 50 objetos Producto.
    // Ejemplo: vector<Producto> listaProductos;

    // [EDUARDO - TODO #23] Crea un arreglo constante de strings para las 'Categorías'.
    // Ejemplo: "Electrónica", "Ropa", "Libros", "Hogar".
    
    // [EDUARDO - TODO #24] Crea un arreglo constante de strings para 'Nombres de Producto'.
    // Ejemplo: "Smartphone", "Camiseta", "Sofá", "Novela", "Laptop", "Pantalones".

    for (int i = 0; i < 50; i++) {
        
        // [FEDE - TODO #26] Genera un ID secuencial.
        // Como 'i' aumenta en 1 cada vez, el 'id' puede ser simplemente 'i + 1'.
        int id = i + 1;
        // [FEDE - TODO #27] Genera un índice aleatorio para elegir un Nombre y una Categoría de los arreglos de Eduardo.
        // Usa el operador módulo %. Ejemplo: rand() % cantidadDeNombres.
        int idNombre = rand() % cantidadDeNombres;
        int idCategoria = rand() % cantidadDeCategorias;
        // [FEDE - TODO #28] Genera un Precio aleatorio (float).
        // Lógica: (rand() % rango) + minimo. Asegúrate de convertirlo a float.
        float precio = (float)(rand() % 991) + 10;
        // [FEDE - TODO #29] Genera un Stock aleatorio (int).
        // Lógica: Número aleatorio entre 0 y 100.
        int stock = rand() % 101;
        // [FEDE - TODO #30] Genera una Calificación Promedio aleatoria (float).
        // Lógica: Flotante aleatorio entre 1.0 y 5.0.
        float CalProale = (rand() % 401)/100.0f + 1.0f;
        // [EDUARDO - TODO #31] Instancia un nuevo objeto 'Producto' usando los valores que Fede generó.
        // Pasa las variables al constructor.

        // [EDUARDO - TODO #32] Agrega este nuevo objeto al vector 'listaProductos' (usando push_back).
    }

    // [EDUARDO & FEDE - TODO #33] Creen un bucle final para recorrer el vector 
    // y llamar a 'mostrarInfo()' en cada producto para probar que el código funciona.
    // Podriamos hacer que recorra los id?

    return 0;
}
