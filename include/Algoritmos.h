#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <vector>
#include <functional> 
#include <string>     
#include "Producto.h"

// 1. INSERTION SORT
void insertionSort(std::vector<Producto>& arr, std::function<bool(const Producto&, const Producto&)> comp) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Producto key = arr[i];
        int j = i - 1;
        while (j >= 0 && comp(key, arr[j])) { 
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 2. QUICK SORT
int partition(std::vector<Producto>& arr, int low, int high, std::function<bool(const Producto&, const Producto&)> comp) {
    Producto pivot = arr[high]; 
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++) {
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

// Función wrapper (la que llama el main)
void runQuickSort(std::vector<Producto>& arr, std::function<bool(const Producto&, const Producto&)> comp) {
    quickSort(arr, 0, arr.size() - 1, comp);
}

// 3. MERGE SORT
void merge(std::vector<Producto>& arr, int l, int m, int r, std::function<bool(const Producto&, const Producto&)> comp) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<Producto> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        // La condición extra mantiene estabilidad básica si son iguales
        if (comp(L[i], R[j]) || (!comp(R[j], L[i]) && !comp(L[i], R[j]))) { 
             arr[k] = L[i]; i++;
        } else {
             arr[k] = R[j]; j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
}

void mergeSort(std::vector<Producto>& arr, int l, int r, std::function<bool(const Producto&, const Producto&)> comp) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comp);
        mergeSort(arr, m + 1, r, comp);
        merge(arr, l, m, r, comp);
    }
}

// Función wrapper (la que llama el main)
void runMergeSort(std::vector<Producto>& arr, std::function<bool(const Producto&, const Producto&)> comp) {
    if (!arr.empty())
        mergeSort(arr, 0, arr.size() - 1, comp);
}
// BUSQUEDAS
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

// Busqueda Lineal por Subcadena
std::vector<int> linearSearchSubstr(const std::vector<Producto>& arr, std::string subcadena) {
    std::vector<int> resultados;
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i].getNombre().find(subcadena) != std::string::npos) {
            resultados.push_back(i);
        }
    }
    return resultados;
}

#endif
