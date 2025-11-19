// [ELIAS - TODO #1] Añade las "Include Guards" (#ifndef, #define) para evitar errores de duplicación.
#ifndef PRODUCTO_H
#define PRODUCTO_H

// [ELIAS - TODO #2] Incluye la librería <string> para manejar texto y <iostream>.
#include <string>
#include <iostream>

// [ELIAS - TODO #3] Define la clase llamada 'Producto'.
class Producto {

private:
    // [ELIAS - TODO #4] Declara el atributo: 'id' (int).
    // [ELIAS - TODO #5] Declara el atributo: 'nombre' (std::string).
    // [ELIAS - TODO #6] Declara el atributo: 'precio' (float o double).
    // [ELIAS - TODO #7] Declara el atributo: 'categoria' (std::string).
    // [ELIAS - TODO #8] Declara el atributo: 'stock' (int).
    // [ELIAS - TODO #9] Declara el atributo: 'calificacionPromedio' (float).

public:
    // [ELIAS - TODO #10] Declara el prototipo del Constructor con parámetros.
    // Debe recibir argumentos para todos los atributos listados arriba.
    Producto(int id, std::string nombre, double precio, std::string categoria, int stock, float calificacionPromedio);

    // [ELIAS - TODO #11] Declara un Constructor Vacío/Por defecto.
    Producto();

    // [ELIAS - TODO #12] Declara los "Getters" para todos los atributos (getId, getNombre, etc.).
    // Esto permitirá que el main.cpp lea los valores más tarde.
    int getId() const;
    std::string getNombre() const;
    double getPrecio() const;
    std::string getCategoria() const;
    int getStock() const;
    float getCalificacionPromedio() const;

    // [ELIAS - TODO #13] (Opcional) Declara un método 'mostrarInfo()' para imprimir los detalles del producto fácilmente.
    void mostrarInfo() const;
};

// [ELIAS - TODO #14] Cierra el Include Guard (#endif).
#endif
