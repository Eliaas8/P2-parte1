#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <vector>
#include <functional> // Permite pasar funciones (reglas de ordenamiento) como parametros
#include <string>     // Necesario para buscar texto dentro de nombres
#include "Producto.h"

// INSERTION SORT
// Logica: Acomoda los elementos uno por uno, como ordenar cartas en la mano.
void insertionSort(std::vector<Producto>& arr, std::function<bool(const Producto&, const Producto&)> comp) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Producto key = arr[i];
        int j = i - 1;
        
        // Mueve los elementos para abrir espacio al nuevo
        while (j >= 0 && !comp(arr[j], key)) { 
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// QUICK SORT
// Logica: Elige un punto medio (pivote) y manda los chicos a la izquierda y grandes a la derecha.

int partition(std::vector<Producto>& arr, int low, int high, std::function<bool(const Producto&, const Producto&)> comp) {
    Producto pivot = arr[high]; 
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // Si cumple la condicion, lo mandamos al lado izquierdo del pivote
        if (comp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<Producto>& arr, int low, int high, std::function<bool(const Producto&, const Producto&)> comp) {
    if (low < high) {
        int pi = partition(arr, low, high, comp);
        quickSort(arr, low, pi - 1, comp);
        quickSort(arr, pi + 1, high, comp);
    }
}

// Funcion publica para iniciar el sort facilmente
void runQuickSort(std::vector<Producto>& arr, std::function<bool(const Producto&, const Producto&)> comp) {
    if (arr.empty()) return;
    quickSort(arr, 0, arr.size() - 1, comp);
}


// MERGE SORT
// Logica: Divide la lista en pedacitos y los vuelve a unir ya ordenados.

void merge(std::vector<Producto>& arr, int left, int mid, int right, std::function<bool(const Producto&, const Producto&)> comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Producto> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comp(L[i], R[j])) { 
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<Producto>& arr, int left, int right, std::function<bool(const Producto&, const Producto&)> comp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, comp);
    mergeSort(arr, mid + 1, right, comp);
    merge(arr, left, mid, right, comp);
}

// Funcion publica para iniciar el sort facilmente
void runMergeSort(std::vector<Producto>& arr, std::function<bool(const Producto&, const Producto&)> comp) {
    if (arr.empty()) return;
    mergeSort(arr, 0, arr.size() - 1, comp);
}

// busca binaria
// Requisito: La lista TIENE que estar ordenada por ID antes de usar esto.

int binarySearch(const std::vector<Producto>& arr, int targetId) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid].getId() == targetId) return mid;
        // Cortamos la busqueda a la mitad en cada paso
        if (arr[mid].getId() < targetId) left = mid + 1;
        else right = mid - 1;
    }
    return -1; // -1 significa que no existe
}

// BUSQUEDA LINEAL (Por Nombre)
// Logica: Revisa uno por uno hasta encontrar coincidencias.

std::vector<int> linearSearchSubstr(const std::vector<Producto>& arr, std::string subcadena) {
    std::vector<int> resultados;
    for (size_t i = 0; i < arr.size(); i++) {
        // Si 'find' devuelve algo diferente a npos, encontro el texto
        if (arr[i].getNombre().find(subcadena) != std::string::npos) {
            resultados.push_back(i);
        }
    }
    return resultados;
}

#endif
