#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <iostream>


class Producto {

private:
    int id;// [ELIAS - TODO #4] Declara el atributo: 'id' (int).
    std::string nombre// [ELIAS - TODO #5] Declara el atributo: 'nombre' (std::string).
    double precio;// [ELIAS - TODO #6] Declara el atributo: 'precio' (float o double).
    std::string categoria;// [ELIAS - TODO #7] Declara el atributo: 'categoria' (std::string).
    int stock;// [ELIAS - TODO #8] Declara el atributo: 'stock' (int).
    float clasificacionPromedio// [ELIAS - TODO #9] Declara el atributo: 'calificacionPromedio' (float).

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
