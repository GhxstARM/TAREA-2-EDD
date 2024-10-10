#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;



struct Pelicula {
    string nombre ;
    string director ;
    float rating ;
};

class Director {
    private :
        struct lNodo {
            Pelicula * val ;
            lNodo * sig ;
        };
        Director () ; // constructor
        ~ Director () ; // destructor
        lNodo * head ;
        lNodo * curr ;
        lNodo * tail ;
        size_t size ; // longitud lista
        string nombre_director ;
        public :
            void agregar_pelicula ( Pelicula * pelicula ); // agrega pelicula al final de la lista enlazada
            void ordenar () ; // ordena la lista
            void calcular_rating_promedio () ;
            void mostrar_peliculas () ;
};



class Arboles {
    private :
        struct aNodo {
            Director * val ;
            aNodo * izq ;
            aNodo * der ;
        };
        aNodo * root_1 ; // raiz arbol ordenado por directores
        aNodo * curr_1 ;
        size_t size_1 ;
        aNodo * root_2 ; // raiz arbol ordenado por rating
        aNodo * curr_2 ;
        size_t size_2 ;
    public :
        Arboles () ; // constructor
        ~ Arboles () ; // destructor
        void insertar_pelicula ( Pelicula * pelicula );
        void copiar_arbol (); // hace copia de arbol 1 en arbol 2 ordenado respecto de rating
        Director * buscar_director ( string director ); // retorna arreglo de peliculas
        Pelicula * buscar_pelicula ( string pelicula ); // retorna peliculas
};



int main(){

    cout<<"prueba"<<endl;


    return 0;
    
}