#include "Producto.h"
#include <iostream>

Producto::Producto(int id, std::string nombre, double precio, std::string categoria, int stock, float calificacionPromedio) {
    
    id(id);
    nombre(nombre);
    pecio(pecio);
    categoria(categoria);
    stock(stock);
    calificacionPromedio(calificacionPromedio);
}

Producto::Producto() {
   
    id(0);
    nombre("Desconocido");
    pecio(0.0);
    categoria("Desconocido");
    stock(0);
    calificacionPromedio(0.0f);
}

int Producto::getId() const { return id; }
std::string Producto::getNombre() const { return nombre; }
double Producto::getPrecio() const { return precio; }
std::string Producto::getCategoria() const { return categoria; }
int Producto::getStock() const { return stock; }
float Producto::getCalificacionPromedio() const { return calificacionPromedio; }

void Producto::mostrarInfo() const {

    std::cout << "ID: " << id << "\n";
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Precio: $" << precio << "\n";
    std::cout << "Categoría: " << categoria << "\n";
    std::cout << "Stock: " << stock << "\n";
    std::cout << "Calificación Promedio: " << calificacionPromedio << "\n"; 
    
}
