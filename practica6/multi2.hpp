/* Álvaro de Francisco Nievas (838819) y Guillermo Bajo Laborda (842748)
*/

#ifndef MULTICONJUNTO_HPP
#define MULTICONJUNTO_HPP

#include "pila.hpp"


using namespace std;

template<typename T> struct multiconjunto;

// OPERACIONES PÚBLICAS
template<typename T> void vacio (multiconjunto<T>& m);
template<typename T> void agnadir (multiconjunto<T>& m, T& e);
template<typename T> bool quitar (multiconjunto<T>& m, T& e);
template<typename T> int multiplicidad (multiconjunto<T>& m, T& e);
template<typename T> int cardinal (const multiconjunto<T>& m);
template<typename T> void liberar(multiconjunto<T>& m);


// OPERACIONES DE ITERADOR: lo recorre de menor a mayor
template<typename T> void iniciarIterador(multiconjunto<T>& m);
template<typename T> bool existeSiguiente(multiconjunto<T>& m);
template<typename T> void siguiente(multiconjunto<T>& m, T& e, int &multiplicidad, bool& error);


//OPERACIONES PRIVADAS
template<typename T> void insertar(typename multiconjunto<T>::Nodo *&a, T& e, bool& agnadido);
template<typename T> void borrar(typename multiconjunto<T>::Nodo* &a, T& e, bool& eliminado);
template<typename T> void borrarMax(typename multiconjunto<T>::Nodo* &a, T& e);
template<typename T> void esta(typename multiconjunto<T>::Nodo* &a, T& e, int& res, bool& esta);
template<typename T> void liberarRec(typename multiconjunto<T>::Nodo* &a);


// DECLARACIÓN DEL TAD GENÉRICO multiconjunto

template<typename T>
struct multiconjunto {  

    friend void vacio<T>(multiconjunto<T>& m);
    friend void agnadir <T>(multiconjunto<T>& m, T& e);
    friend bool quitar <T>(multiconjunto<T>& m, T& e);
    friend int multiplicidad <T>(multiconjunto<T>& m, T& e);
    friend int cardinal <T>(const multiconjunto<T>& m);
    friend void liberar<T>(multiconjunto<T>& m);
    friend void iniciarIterador<T>(multiconjunto<T>& m);
    friend bool existeSiguiente<T>(multiconjunto<T>& m);
    friend void siguiente<T>(multiconjunto<T>& m, T& e, int &multiplicidad, bool& error);

  private: 

    struct Nodo {
        T dato;
        int multiplicidad = 0;
        Nodo* izq;
        Nodo* der;
    };

    friend void insertar<T>(typename multiconjunto<T>::Nodo *&a, T& e, bool& agnadido);
    friend void borrar<T>(typename multiconjunto<T>::Nodo *&a, T& e, bool& eliminado);
    friend void borrarMax<T>(typename multiconjunto<T>::Nodo *&a, T& e);
    friend void esta<T>(typename multiconjunto<T>::Nodo *&a, T& e, int& res, bool& esta);
    friend void liberarRec<T>(typename multiconjunto<T>::Nodo *&a);

    int cardinal;
    Nodo* raiz;
    Pila<Nodo*> iterador;
};


// IMPLEMENTACIÓN DE LAS OPERACIONES DEL TAD GENÉRICO

// devuelve un multiconjunto vacío, sin elementos
template<typename T>
void vacio (multiconjunto<T>& m) {
    m.cardinal = 0;
    m.raiz = nullptr;
}   


// añadir: multi m, elemento e -> multi
// devuelve el multiconjunto igual al resultante de añadir un ejemplar del elemento e a m
template<typename T>
void agnadir (multiconjunto<T>& m, T& e) {
    bool agnadido;
    insertar(m.raiz, e, agnadido);
    if(agnadido){
        m.cardinal++;
    }
}

// devuelve el multiconjunto igual al resultante de extraer un ejemplar del elemento e de m;
// si no hay ningún elemento e en m, devuelve un multiconjunto igual a m
template<typename T>
bool quitar (multiconjunto<T>& m, T& e) {
    bool quitado;
    borrar(m.raiz, e, quitado);
    if(quitado){
        m.cardinal--;
    }
}


// devuelve el nº de ejemplares del elemento e que hay en m (0 si no hay ninguno)
template<typename T>
int multiplicidad (multiconjunto<T>& m, T& e) {
    bool exito;
    int res;
    esta(m.raiz, e, res, exito);

    if(exito){
        return res;
    }
    else{
        return 0;
    }
}


// devuelve el número total de elementos en m, contando los repetidos
template<typename T>
int cardinal (const multiconjunto<T>& m) {
    return m.cardinal;
}


//Libera toda la memoria utilizada por el diccionario, y deja en d diccionario vacío
template<typename T>
void liberar(multiconjunto<T>& m){
    liberar(m.iterador);
    liberarRec(m.raiz);
    m.cardinal = 0;
}


// OPERACIONES DE ITERADOR: lo recorre de menor a mayor

// Prepara el iterador para que el SIGUIENTE ELEMENTO A VISITAR sea el menor de todo el
// multiconjunto m (según la operación menor del parámetro formal elemento), si existe
// (i.e., situación de no haber visitado ningún elemento).
template<typename T>
void iniciarIterador(multiconjunto<T>& m) {
    crearVacia(m.iterador);
    typename multiconjunto<T>::Nodo* aux;

    liberar(m.iterador);         //eliminar restos de recorridos anteriores (no exhaustivos) y empezar con pila vacía
    aux = m.raiz;                //raíz del árbol
    while(aux != nullptr){
        apilar(m.iterador, aux); //apila puntero a nodo del árbol, en la pila del iterador
        aux = aux->izq;
    }
}


// Devuelve falso si ya se han visitado todos los elementos de m, devuelve verdad en
// caso contrario
template<typename T>
bool existeSiguiente(multiconjunto<T>& m) {
    return (!esVacia(m.iterador));
}



// devuelve el siguiente elemento y su multiplicidad, y avanza el iterador. 
template<typename T>
void siguiente(multiconjunto<T>& m, T& e, int& multiplicidad, bool& error){
    typename multiconjunto<T>::Nodo* aux;

    if(existeSiguiente(m)){
        error = false;
        cima(m.iterador, aux, error);
        e = aux->dato;
        multiplicidad = aux->multiplicidad;
        //avanzar
        desapilar(m.iterador);
        aux = aux->der;
        while(aux != nullptr){
            apilar(m.iterador, aux);
            aux = aux->izq;
        }
    }
    else{
        error = true;
    }
}





// FUNCIONES INTERNAS AUXILIARES, NO USARLAS FUERA DE ESTE MÓDULO

template<typename T>
void insertar(typename multiconjunto<T>::Nodo *&a, T& e, bool& agnadido){
    if(a == nullptr){
        a = new typename multiconjunto<T>::Nodo;
        a->dato = e;
        a->multiplicidad++;
        a->izq = nullptr;
        a->der = nullptr;
        agnadido = true;
    }
    else{
        if(e < a->dato){
            insertar(a->izq, e, agnadido);
        }
        else if(e > a->dato){
            insertar(a->der, e, agnadido);
        }
        else{
            a->multiplicidad++;
            agnadido = true;
        }
    }
}


template<typename T>
void borrar(typename multiconjunto<T>::Nodo *&a, T& e, bool& eliminado){
    typename multiconjunto<T>::Nodo* aux;
    if(a != nullptr){
        if(e < a->dato){
            borrar(a->izq, e, eliminado);
        }
        else if(e > a->dato){
            borrar(a->der, e, eliminado);
        }
        else if(e == a->dato){
            if(a->multiplicidad > 1){
                a->multiplicidad--;
            } 
            else {
                if(a->izq == nullptr){
                    aux = a;
                    a = a->der;
                    delete aux;
                }

                else{           //ambos hijos son no vacíos
                    borrarMax(a->izq, a->dato);
                }
            }
            eliminado = true;
        }
    }
    else{
        eliminado = false;
    }
}


template<typename T>
void borrarMax(typename multiconjunto<T>::Nodo *&a, T& e){
    typename multiconjunto<T>::Nodo* aux;
    if(a->der == nullptr){
        e = a->dato;
        aux = a;
        a = a->izq;
        delete aux;
    }
    else{
        borrarMax(a->der, e);
    }
}



template<typename T>
void esta(typename multiconjunto<T>::Nodo *&a, T& e, int& res, bool& aparece){
    if(a == nullptr){
        aparece = false;
    }
    else{
        if(e < a->dato){
            esta(a->izq, e, res, aparece);
        }
        else if(e > a->dato){
            esta(a->der, e, res, aparece);
        }
        else if(e == a->dato){
            aparece = true;
            res = a->multiplicidad;
        }
    }
}


//Libera toda la memoria utilizada por el árbol a, en el que se almacenan los datos del 
//diccionario, y deja en a el árbol vacío
template<typename T>
void liberarRec(typename multiconjunto<T>::Nodo* a){
    if(a != nullptr){
        liberarRec(a->izq);
        liberarRec(a->der);
        delete a;
        a = nullptr;
    }
}



#endif