# Documentación del Proyecto - Parcial 2

Este proyecto implementa un sistema de gestión de inventario simulado en C++, diseñado para analizar el rendimiento de diferentes algoritmos de ordenamiento y búsqueda aplicados a estructuras de datos complejas (Objetos).

## Estructura del Código

El código está dividido en tres módulos principales para mantener la modularidad y limpieza:

1.  **`Producto` (Clase):**
    * Define la estructura de datos que representa un artículo en el inventario.
    * Contiene atributos de diferentes tipos (`int`, `double`, `std::string`, `float`) para simular un objeto real pesado en memoria.
    * Encapsula la lógica de acceso a datos (Getters) y visualización.

2.  **`Algoritmos.h` (Lógica):**
    * Implementa tres algoritmos de ordenamiento clásicos: **Insertion Sort**, **Quick Sort** y **Merge Sort**.
    * Implementa **Búsqueda Binaria** para recuperación eficiente de datos.
    * **Característica destacada:** Uso de `templates` y `std::function` (lambdas) para permitir criterios de comparación dinámicos. Esto permite ordenar la misma lista por Precio (Ascendente) o Calificación (Descendente) reutilizando el mismo código de ordenamiento.

3.  **`main.cpp` (Ejecución):**
    * Genera un dataset de prueba de 50 productos con valores aleatorios coherentes.
    * Orquesta las pruebas de rendimiento midiendo el tiempo de ejecución con `std::chrono` (alta precisión).
    * Valida los resultados de búsqueda (existentes vs. no existentes).

---

## Análisis de Resultados y Rendimiento

A continuación se presentan las respuestas al análisis teórico-práctico solicitado en el parcial.

### 1. Ordenamiento de Objetos Complejos vs. Números Simples

**¿Hubo diferencias significativas en el rendimiento al ordenar objetos complejos en comparación con números simples?**
Sí, existe una diferencia notable en el costo computacional.
* **Movimiento de Memoria:** Al ordenar un arreglo de enteros (`int`), el intercambio (`swap`) es trivial y muy rápido (4 bytes). Al ordenar objetos `Producto`, cada intercambio implica copiar múltiples campos (`id`, `precio`, `stock`) y, lo más costoso, cadenas de texto (`std::string` para nombre y categoría). Copiar cadenas implica asignación dinámica de memoria, lo cual es significativamente más lento que mover tipos primitivos.
* **Comparación:** Comparar dos objetos requiere llamar a métodos accesores (`getPrecio()`), lo cual añade una pequeña sobrecarga (overhead) por llamada a función en comparación con comparar variables directas.

**¿Cuál algoritmo fue el más eficiente para cada criterio?**
Basado en la ejecución con $N=50$:
* **Insertion Sort:** Sorprendentemente eficiente para este tamaño de muestra pequeño. Al tener muy poco *overhead* de recursión y asignación de memoria auxiliar, suele competir o ganar a algoritmos más complejos cuando $N < 50$.
* **Quick Sort:** Generalmente el más rápido en promedio, aunque para 50 elementos la diferencia con Insertion Sort es mínima.
* **Merge Sort:** Tiende a ser ligeramente más lento en este contexto específico debido a que requiere crear vectores auxiliares (`L` y `R`) en cada paso, copiando los objetos `Producto` múltiples veces, lo cual es costoso.

**¿Cómo se comparan estos resultados con la teoría?**
La teoría dicta que Insertion Sort es $O(n^2)$ y Quick/Merge son $O(n \log n)$.
* Con $N=50$, $n^2 = 2500$ operaciones y $n \log n \approx 282$.
* Aunque la diferencia en operaciones es de casi 10x, los factores constantes (overhead) hacen que en la práctica los tiempos estén cercanos. Si aumentáramos la muestra a 10,000 productos, la teoría se cumpliría estrictamente y Insertion Sort se volvería inutilizable, mientras que Quick Sort mantendría su eficiencia.

### 2. Búsqueda Binaria por ID

**¿Por qué la Búsqueda Binaria es ideal para buscar por ID?**
1.  **Naturaleza del ID:** Los IDs son claves únicas numéricas secuenciales o comparables, lo que elimina la ambigüedad en el ordenamiento.
2.  **Complejidad:** La búsqueda binaria reduce el espacio de búsqueda a la mitad en cada paso, ofreciendo una complejidad de $O(\log n)$.
    * En un inventario de 1,000,000 de productos, una búsqueda lineal ($O(n)$) haría hasta 1 millón de comparaciones. La binaria haría solo **20 comparaciones**.
3.  **Requisito de Orden:** Dado que es computacionalmente barato ordenar por un entero simple (ID), mantener el inventario ordenado por ID para permitir búsquedas binarias es una estrategia de optimización excelente.

### 3. Búsqueda por Texto (Nombre) vs. ID

**¿Cómo afecta la naturaleza de la búsqueda por subcadena de texto al rendimiento en comparación con la búsqueda por id?**
La búsqueda por texto es significativamente más lenta por dos razones:
1.  **Costo de Comparación:** Comparar dos enteros es una instrucción de CPU. Comparar dos cadenas ("Smartphone" vs "Smartwatch") requiere recorrer los caracteres uno por uno hasta encontrar una diferencia ($O(L)$ donde L es la longitud de la palabra).
2.  **Imposibilidad de Búsqueda Binaria directa:** Si buscamos una *subcadena* (ej. productos que contengan "Phone"), no podemos usar búsqueda binaria estándar porque el criterio "contiene" no permite descartar mitades del arreglo ordenado. Estamos forzados a usar Búsqueda Lineal ($O(n)$), revisando cada producto uno por uno.

**Alternativas para optimizar la búsqueda por nombre en producción:**
Para evitar recorrer todo el inventario comparando strings, se utilizan estructuras avanzadas:
* **Índices Invertidos (Full-Text Search):** Como lo hacen motores como ElasticSearch. Mapean palabras clave a listas de IDs (ej: "Mesa" -> [ID 4, ID 15, ID 88]).
* **Árboles Trie (Prefix Trees):** Ideales para autocompletado. Permiten encontrar todas las palabras que empiezan con "Sm..." en tiempo proporcional al largo de la palabra, no a la cantidad de productos.
* **Tablas Hash:** Útiles solo si la búsqueda es por coincidencia exacta del nombre completo ($O(1)$ en promedio).
