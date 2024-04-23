/* Álvaro de Francisco Nievas (838819) y Guillermo Bajo Laborda (842748).

  Programa que lee un fichero de texto y escribe en otro en primer lugar las palabras que 
  no estaban repetidas, ordenadas alfabéticamente, una en cada línea, y a continuación el 
  resto de las palabras del fichero de entrada (las que aparecían repetidas), ordenadas 
  alfabéticamente, una en cada línea, y cada una seguida de un espacio en blanco y del 
  número de veces que aparece repetida en el fichero de entrada.
*/

#include <iostream>
#include <fstream>
#include <string>

#include "multi2.hpp"
#include "colaprio.hpp"


using namespace std;    

const string FICH_ENTRADA = "entrada.txt";
const string FICH_SALIDA = "salida.txt";

struct elm {
    string palabra;
    int multi = 0;
};


// Pre:  <multiconjuncad> está iniciado y <nomFich> ses el nombre del fichero a leer.
// Post: Se han leído las cadenas almacenadas en <nomFich> (una por línea) y se han 
//       almacenado en el multiconjunto <multiconjuntocad>. Devuelve true si todo ha 
//       salido como esperado, false en caso contrario.
bool cargarDatos(const string nomFich, multiconjunto<string>& multiconjuntocad){
    
    ifstream inf;
    inf.open(nomFich); //Abre fichero de lectura
    
    if (inf.is_open()){

        string palabraLeida;
        string salto;

        while (inf >> palabraLeida) {
            agnadir(multiconjuntocad, palabraLeida); //Lee y añade la palabra
            getline(inf, salto); //Omite salto de línea
        }
        inf.close();

        return true;
    }
    else //Si no se ha podido abrir
        return false;
}


// Pre:  <multiconjuncad> y <cola> están iniciados. <cola> está vacio, <multiconjugad> contiene las
//       palabras.
// Post: Recorre las palabras del multiconjunto creado y las introduce (con sus multiplicidades) 
//       en <cola> (guardando un elemento por cada palabra distinta del multiconjunto), de forma 
//       que: una palabra será priorizada en la cola si y sólo si tiene multiplicidad igual a uno. 
void llenaColaPrio(multiconjunto<string>& multiconjuntocad, colaprio<elm>& cola) {

    elm e;
    bool error;
    
    siguiente(multiconjuntocad, e.palabra, e.multi, error); //Lee el primer elemento

    while (!error) {

        bool esPrio = (e.multi == 1); //Comprueba si es elemento prioritario
            
        encolarCP(cola, e, esPrio); //Encola

        siguiente(multiconjuntocad, e.palabra, e.multi, error); //Lee el siguiente elemento
    }
}


// Pre:  <cola> está iniciada y <nomFich> ses el nombre del fichero a escribir
// Post: Si devuelve true se ha creado el fichero <nomFich> y en el se encuentran las palabras de la cola.
//       Primero aparecen (si hay) las palabras con multiplicidad 1, ordenadas alfabeticamente. Después 
//       aparecen las palabras de multiplicidad > 1 ordenadas alfabéticamente.
bool salidaDatos(const string nomFich, colaprio<elm>& cola) {

    ofstream outf;
    outf.open(nomFich); //Abre fichero de lectura
    
    if (outf.is_open()){
        
        bool error = false;
        elm e;
        
        while(existeSiguienteCP(cola)){
            siguienteYAvanzaCP(cola, e, error); //Lee elemento
            if(!error){
                outf << e.palabra; //Escribe elemento
                if (e.multi != 1)
                    outf << " " << e.multi; //Escribe multiplicidad elemento (si mult > 1)
                
                outf << "\n";
            }
        }
        outf.close();
            
        return true;
    }
    else //Si no se ha podido abrir
        return false;
}



int main() 
{
    multiconjunto<string> multiconjuntocad;
    vacio(multiconjuntocad); 

    if(!cargarDatos(FICH_ENTRADA, multiconjuntocad)) return -1;
    
    colaprio<elm> cola;
    iniciar(cola);
    iniciarIterador(multiconjuntocad);
    
    llenaColaPrio(multiconjuntocad, cola);

    iniciarIteradorCP(cola);

    if (!salidaDatos(FICH_SALIDA, cola)) return -1;
    
    return 0;   
}