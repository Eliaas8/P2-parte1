#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <vector>
#include <functional> 
#include <string>     // Necesario para busqueda de texto
#include "Producto.h"

// ... (KEEP YOUR EXISTING SORTING FUNCTIONS HERE: Insertion, Quick, Merge) ...
// ... (MANTEN TUS FUNCIONES DE ORDENAMIENTO AQUI: Insertion, Quick, Merge) ...
// ... DO NOT DELETE THEM ...

// Busqueda Binaria (Requiere estar ordenado por ID previamente)
int binarySearch(const std::vector<Producto>& arr, int targetId) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid].getId() == targetId) return mid;
        if (arr[mid].getId() < targetId) left = mid + 1;
        else right = mid - 1;
    }
    return -1; // No encontrado
}

// NUEVO: Busqueda Lineal por Subcadena (Requisito Parte 3)
// Retorna un vector con todos los indices encontrados (ya que pueden haber varios "Smartphones")
std::vector<int> linearSearchSubstr(const std::vector<Producto>& arr, std::string subcadena) {
    std::vector<int> resultados;
    for (size_t i = 0; i < arr.size(); i++) {
        // string::npos significa "no encontrado". Si es diferente, es que existe.
        if (arr[i].getNombre().find(subcadena) != std::string::npos) {
            resultados.push_back(i);
        }
    }
    return resultados;
}

#endif
