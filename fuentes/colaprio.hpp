/* Álvaro de Francisco Nievas (838819) y Guillermo Bajo Laborda (842748)
*/

#ifndef COLAPRIO_HPP
#define COLAPRIO_HPP

#include "cola.hpp"


template<typename T> struct colaprio;


/* Devuelve una cola vacía, sin elementos
*/
template<typename T> void iniciar(colaprio<T>& c);


/* Devuelve una cola igual a la resultante de añadir elem a c como elemento prioritario si
 prio es verdad o como no prioritario en caso contrario
*/
template<typename T> void encolarCP(colaprio<T>& c, const T& e, bool esPrio);


/* Devuelve verdad si y sólo si c no tiene elementos
*/
template<typename T> bool esVaciaCP(const colaprio<T>& c);


/* Devuelve el primer elemento encolado como prioritario de los que hay en c. Si no hay
 ningún elemento prioritario, devuelve el primer elemento encolado como no prioritario.
 Parcial: la operación no está definida si c es vacía.
*/
template<typename T> void primeroCP(colaprio<T>& c, T& e, bool& error);


/* Si esVacía(c), devuelve la cola vacía. En caso contrario, devuelve una cola igual a la
 resultante de eliminar de c su elemento primero, es decir, si en c hay elementos
 prioritarios elimina el primero de ellos que fue encolado; si no los hay, elimina el
 primero de los no prioritarios que fue encolado.
*/
template<typename T> void desencolarCP(colaprio<T>& c);


/* Devuelve el número de elementos de c
*/
template<typename T> int longitudCP(const colaprio<T>& c);


/* Si prio es verdad, devuelve el número de elementos prioritarios de c; en caso
 contrario, devuelve el número de elementos no prioritarios de c.
*/
template<typename T> int longClase(const colaprio<T>& c, bool esPrio);


// OPERACIONES ITERADOR

/*  Prepara el iterador para que el siguiente elemento a visitar sea el primero de la
 cola c (entendido según la operación primero(c) especificada antes), si es que existe
 (i.e., situación de no haber visitado ningún elemento).
 */
template<typename T> void iniciarIteradorCP(colaprio<T>& c);


/* Devuelve falso si ya se han visitado todos los elementos de c, devuelve verdad en
 caso contrario
 */
template<typename T> bool existeSiguienteCP(const colaprio<T>& c);


/* Devuelve el siguiente elemento prioritario de c que fue encolado, si lo hay; si por el
 contrario ya no hay más elementos prioritarios en c pendientes de visitar, devuelve el
 siguiente elemento no prioritario de c que fue encolado, si lo hay.
 Parcial: la operación no está definida si no existeSiguiente(c).
 */
template<typename T> void siguienteYAvanzaCP(colaprio<T>& c, T& e, bool& error);



// DECLARACIÓN DEL TAD GENÉRICO COLAPRIO
template<typename T>
struct colaprio{
    friend void iniciar<T>(colaprio<T>& c);
    friend void encolarCP<T>(colaprio<T>& c, const T& e, bool esPrio);
    friend bool esVaciaCP<T>(const colaprio<T>& c);
    friend void primeroCP<T>(colaprio<T>& c, T& e, bool& error);
    friend void desencolarCP<T>(colaprio<T>& c);
    friend int longitudCP<T>(const colaprio<T>& c);
    friend int longClase<T>(const colaprio<T>& c, bool esPrio);
    friend void iniciarIteradorCP<T>(colaprio<T>& c);
    friend bool existeSiguienteCP<T>(const colaprio<T>& c);
    friend void siguienteYAvanzaCP<T>(colaprio<T>& c, T& e, bool& error);
  private: 

    cola<T> colaP;
    cola<T> colaNP;
};


// IMPLEMENTACIÓN DE LAS OPERACIONES DEL TAD GENÉRICO COLAPRIO
template<typename T>
void iniciar(colaprio<T>& c){
    crearVacia(c.colaP);
    crearVacia(c.colaNP);
}


template<typename T>
void encolarCP(colaprio<T>& c, const T& e, bool esPrio){
    if(esPrio){
        encolar(c.colaP, e);
    }
    else{
        encolar(c.colaNP, e);
    }
}


template<typename T>
bool esVaciaCP(const colaprio<T>& c){
    return (esVacia(c.colaNP) && esVacia(c.colaP));
}


template<typename T>
void primeroCP(colaprio<T>& c, T& e, bool& error){
    if (!esVaciaCP(c)) {
        if(!esVacia(c.colaP)){
            T elemP; 
            bool errorP;
            primero(c.colaP, elemP, errorP);
            e = elemP;
            error=errorP;
        }
        else{
            T elemNP; 
            bool errorNP;
            primero(c.colaNP, elemNP, errorNP);
            e = elemNP;
            error=errorNP;
        }
    }
    else{
        error = true;
    }
}


template<typename T>
void desencolarCP(colaprio<T>& c){
    if(!esVaciaCP(c)){
        if (!esVacia(c.colaP)) {
            desencolar(c.colaP);            
        }
        else {
            desencolar(c.colaNP);
        }
    }
}


template<typename T>
int longitudCP(const colaprio<T>& c){
    return longitud(c.colaP) + longitud(c.colaNP);
}


template<typename T> 
int longClase(const colaprio<T>& c, bool esPrio){
    if(esPrio){
        return longitud(c.colaP);
    }
    else{
        return longitud(c.colaNP);
    }
}


//OPERACIONES ITERADOR
template<typename T>
void iniciarIteradorCP(colaprio<T>& c){
    iniciarIterador(c.colaP);
    iniciarIterador(c.colaNP);
}


template<typename T>
bool existeSiguienteCP(const colaprio<T>& c){
    return(existeSiguiente(c.colaP) || existeSiguiente(c.colaNP));
}


template<typename T>
void siguienteYAvanzaCP(colaprio<T>& c, T& e, bool& error) {
    siguienteYAvanza(c.colaP, e, error);

    if(error){
        siguienteYAvanza(c.colaNP, e, error);
   }
}


#endif //fin de colaprio.hpp
