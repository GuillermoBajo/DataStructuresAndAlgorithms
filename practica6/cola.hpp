/* Álvaro de Francisco Nievas (838819) y Guillermo Bajo Laborda (842748)
*/

#ifndef COLA_HPP
#define COLA_HPP

using namespace std;


template<typename T> struct cola;


/* Devuelve una cola vacía, sin elementos
*/
template<typename T> void crearVacia(cola<T>& c);

/* Devuelve una cola igual a la resultante de añadir elem a c como elemento prioritario si
 prio es verdad o como no prioritario en caso contrario
*/
template<typename T> void encolar(cola<T>& c, const T& e);

/* Devuelve verdad si y sólo si c no tiene elementos
*/
template<typename T> bool esVacia(const cola<T>& c);

/* Devuelve el primer elemento encolado como prioritario de los que hay en c. Si no hay
 ningún elemento prioritario, devuelve el primer elemento encolado como no prioritario.
 Parcial: la operación no está definida si c es vacía.
*/
template<typename T> void primero(cola<T>& c, T& e, bool& error);

/* Si esVacía(c), devuelve la cola vacía. En caso contrario, devuelve una cola igual a la
 resultante de eliminar de c su elemento primero, es decir, si en c hay elementos
 prioritarios elimina el primero de ellos que fue encolado; si no los hay, elimina el
 primero de los no prioritarios que fue encolado.
*/
template<typename T> void desencolar(cola<T>& c);

/* Devuelve el número de elementos de c
*/
template<typename T> int longitud(const cola<T>& c);

/* Devuelve en c la cola vacía y además libera la memoria utilizada previamente por c
*/
template<typename T> void liberar(cola<T>& c);

// OPERACIONES ITERADOR

/* Prepara el iterador para que el siguiente elemento a visitar sea un primer elemento 
 * de c, si existe (situación de no haber visitado ningún elemento)
*/
template<typename T> void iniciarIterador(cola<T>& c);

/* Devuelve falso si ya se han visitado todos los elementos de c; devuelve cierto en
 * caso contrario
*/
template<typename T> bool existeSiguiente(const cola<T>& c);

/* Si existe algún elemento de c pendiente de visitar, devuelve en e el siguiente
 * elemento a visitar y error=falso, y además avanza el iterador para que a
 * continuación se pueda visitar otro elemento de c. Si no quedan elementos pendientes
 * de visitar devuelve error=verdad y e queda indefinido
*/
template<typename T> void siguienteYAvanza(cola<T>& c, T& e, bool& error);



// DECLARACIÓN DEL TAD GENÉRICO COLA

template<typename T>
struct cola{
    friend void crearVacia<T>(cola<T>& c);
    friend void encolar<T>(cola<T>& c, const T& e);
    friend bool esVacia<T>(const cola<T>& c);
    friend void primero<T>(cola<T>& c, T& e, bool& error);
    friend void desencolar<T>(cola<T>& c);
    friend int longitud<T>(const cola<T>& c);
    friend void liberar<T>(cola<T>& c);
    friend void iniciarIterador<T>(cola<T>& c);
    friend bool existeSiguiente<T>(const cola<T>& c);
    friend void siguienteYAvanza<T>(cola<T>& c, T& e, bool& error);
  private: 
  
    struct Nodo {
        T dato; 
        Nodo* sig;			
    };
    Nodo* pri;
    Nodo* ult;
    int numDatos;
    Nodo* iter;
};


//OPERACIONES DEL TAD GENÉRICO COLA
template<typename T>
void crearVacia(cola<T>& c){
    c.pri = nullptr;
    c.ult = nullptr;
    c.numDatos = 0;
}


template<typename T>
void encolar (cola<T>& c, const T& e) { 
    if (c.numDatos == 0) {
        c.ult = new typename cola<T>::Nodo;
        c.pri = c.ult;
    }
    else {
        c.ult->sig = new typename cola<T>::Nodo;
        c.ult = c.ult->sig;
    }
    c.ult->dato = e;
    c.ult->sig = nullptr;
    c.numDatos++;
}


template<typename T>
bool esVacia(const cola<T>& c){
    return c.pri == nullptr;
}


template<typename T>
void primero(cola<T>& c, T& elem, bool& error){
    if(!esVacia(c)){
        error = false;
        elem = c.pri->dato;
    }
    else{
        error = true;
    }
}


template<typename T>
void desencolar(cola<T>& c){
    typename cola<T>::Nodo* aux;
    if(!esVacia(c)){
        aux = c.pri;
        c.pri = c.pri->sig;
        delete (aux);
        c.numDatos--;
        if(c.numDatos == 0){
            c.ult = nullptr;
        }
    }
}


template<typename T>
int longitud(const cola<T>& c){
    return c.numDatos;
}


template<typename T>
void liberar(cola<T>& c){
    typename cola<T>::Nodo* aux = c.pri;
    while(aux != nullptr){
        c.pri = c.pri->sig;
        delete(aux);
        aux = c.pri;
    }
    c.ult = nullptr;
    c.numDatos = 0;    
}



//OPERACIONES ITERADOR
template<typename T>
void iniciarIterador(cola<T>& c){
    c.iter = c.pri;
}


template<typename T>
bool existeSiguiente(const cola<T>& c){
    return c.iter != nullptr;
}


template<typename T>
void siguienteYAvanza(cola<T>& c, T& elem, bool& error){
    if (!existeSiguiente(c)) {
        error = true;
    }
    else {
        error = false;
        elem = c.iter->dato;
        c.iter = c.iter->sig;
    }
}


#endif //fin de cola.hpp