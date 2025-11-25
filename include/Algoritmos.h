#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <vector>
#include <functional> // Para pasar funciones como parametros (lambdas)
#include "Producto.h"

// 1. Insertion Sort (Bueno para listas pequeñas)
void insertionSort(std::vector<Producto>& arr, std::function<bool(const Producto&, const Producto&)> comp) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Producto key = arr[i];
        int j = i - 1;
        // Mueve elementos que no cumplen la condicion 'comp'
        while (j >= 0 && !comp(arr[j], key)) { 
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 2. Quick Sort (Divide y venceras, eficiente promedio)
int partition(std::vector<Producto>& arr, int low, int high, std::function<bool(const Producto&, const Producto&)> comp) {
    Producto pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // Si el elemento actual cumple la condicion con respecto al pivot
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

// Wrapper para llamar a quicksort mas facil
void runQuickSort(std::vector<Producto>& arr, std::function<bool(const Producto&, const Producto&)> comp) {
    quickSort(arr, 0, arr.size() - 1, comp);
}

// 3. Merge Sort (Estable y consistente)
void merge(std::vector<Producto>& arr, int left, int mid, int right, std::function<bool(const Producto&, const Producto&)> comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Producto> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comp(L[i], R[j])) { // Usamos el comparador dinamico
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

// Wrapper para merge sort
void runMergeSort(std::vector<Producto>& arr, std::function<bool(const Producto&, const Producto&)> comp) {
    mergeSort(arr, 0, arr.size() - 1, comp);
}

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

#endif
