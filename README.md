# Data Structures And Algorithms

Este programa procesa un archivo de texto (`entrada.txt`) y escribe un archivo de salida (`salida.txt`) con palabras ordenadas de manera específica.

## Aspectos Algorítmicos

1. **Lectura del Archivo de Entrada**:
    - La función `cargarDatos` lee palabras de `entrada.txt` y las almacena en un *multiconjunto* (`multiconjunto`) que mantiene la multiplicidad (repeticiones) de cada palabra.

2. **Organización de Palabras**:
    - Se utilizan dos estructuras de datos para organizar las palabras:
        - Un *multiconjunto* (`multiconjunto`) para almacenar palabras y su multiplicidad.
        - Una *cola priorizada* (`colaprio`) para organizar palabras según su prioridad:
            - Palabras con multiplicidad igual a 1 (no repetidas) se consideran de alta prioridad.
            - Palabras con multiplicidad superior a 1 (repetidas) se consideran de baja prioridad.

3. **Generación de la Cola Priorizada**:
    - La función `llenaColaPrio` itera a través del `multiconjunto` y llena la `cola` con elementos de tipo `elm` (estructura que almacena una palabra y su multiplicidad).
    - Los elementos se encolan según su prioridad, utilizando la función `encolarCP`.

4. **Escritura del Archivo de Salida**:
    - La función `salidaDatos` escribe las palabras de la `cola` en `salida.txt` siguiendo las especificaciones:
        - Palabras con alta prioridad (no repetidas) se escriben primero, ordenadas alfabéticamente.
        - Luego, se escriben palabras con baja prioridad (repetidas) junto con su multiplicidad, ordenadas alfabéticamente.

## Aspectos Estructurales

1. **Estructura de Datos**:
    - Se utiliza un *multiconjunto* (`multiconjunto`) para almacenar palabras con su multiplicidad, implementado como un árbol binario de búsqueda auto-balanceado.
    - Una *cola priorizada* (`colaprio`) organiza palabras según su prioridad, utilizando dos colas: una para palabras con alta prioridad y otra para palabras con baja prioridad.

2. **Manejo de Archivos**:
    - Los archivos `entrada.txt` y `salida.txt` se manejan utilizando flujos de entrada y salida (`ifstream` y `ofstream`).

3. **Iteradores**:
    - Se utilizan iteradores para recorrer tanto el `multiconjunto` como la `cola priorizada` de manera ordenada.

## Conclusión

El programa utiliza estructuras de datos y algoritmos eficientes para organizar las palabras de `entrada.txt` y escribir `salida.txt` de acuerdo con las especificaciones. El uso de *multiconjunto* y *cola priorizada* permite manejar palabras de manera efectiva y ordenada.
