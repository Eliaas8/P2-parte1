#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <iostream>


class Producto {

private:

    int id;
    std::string nombre;
    double precio;
    std::string categoria;
    int stock;
    float calificacionPromedio;


public:
    Producto(int id, std::string nombre, double precio, std::string categoria, int stock, float calificacionPromedio);

    Producto();

    int getId() const;
    std::string getNombre() const;
    double getPrecio() const;
    std::string getCategoria() const;
    int getStock() const;
    float getCalificacionPromedio() const;

    void mostrarInfo() const;
};

// [ELIAS - TODO #14] Cierra el Include Guard (#endif).
#endif
