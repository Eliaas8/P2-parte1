#include "Producto.h"
#include <iostream>

// Constructor con parámetros
Producto::Producto(int id, std::string nombre, double precio, std::string categoria, int stock, float calificacionPromedio) {
    this->id = id;
    this->nombre = nombre;
    this->precio = precio;
    this->categoria = categoria;
    this->stock = stock;
    this->calificacionPromedio = calificacionPromedio;
}

// Constructor por defecto
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

void Producto::mostrarInfo() const {
    std::cout << "[" << id << "] " << nombre 
              << " | Cat: " << categoria 
              << " | $" << precio 
              << " | Stock: " << stock 
              << " | Calif: " << calificacionPromedio << "/5.0\n";
}
