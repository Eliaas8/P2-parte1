#include "Producto.h"
#include <iostream>

// [ELIAS - TODO #16] Implementa el Constructor con Parámetros.
// Usa 'this->variable = variable' o una lista de inicialización para asignar los valores.
Producto::Producto(int id, std::string nombre, double precio, std::string categoria, int stock, float calificacionPromedio) {
    
    this->id = id;
    this->nombre = nombre;
    this->precio = precio;
    this->categoria = categoria;
    this->stock = stock;
    this->calificacionPromedio = calificacionPromedio;
}

// [ELIAS - TODO #17] Implementa el Constructor Por Defecto.
// Inicializa los números en 0 y los strings en vacío o "Desconocido".
Producto::Producto() {

    this->id = 0;
    this->nombre = "Desconocido";
    this->precio = 0.0;
    this->categoria = "Desconocido";
    this->stock = 0;
    this->calificacionPromedio = 0.0f;
}

int Producto::getId() const { return id; }
std::string Producto::getNombre() const { return nombre; }
double Producto::getPrecio() const { return precio; }
std::string Producto::getCategoria() const { return categoria; }
int Producto::getStock() const { return stock; }
float Producto::getCalificacionPromedio() const { return calificacionPromedio; }
// [ELIAS - TODO #19] Implementa 'mostrarInfo()'.
// Usa std::cout para imprimir todos los atributos en un formato legible.
void Producto::mostrarInfo() const {
   
    std::cout << "ID: " << id << "\n";
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Precio: $" << precio << "\n";
    std::cout << "Categoría: " << categoria << "\n";
    std::cout << "Stock: " << stock << "\n";
    std::cout << "Calificación Promedio: " << calificacionPromedio << "\n";
}
