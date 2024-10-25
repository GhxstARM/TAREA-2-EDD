#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
        lNodo * head ;
        lNodo * curr ;
        lNodo * tail ;
        size_t size ; // longitud lista
        string nombre_director ;
    public :
        Director (); // constructor
        ~ Director () ; // destructor
        void agregar_pelicula ( Pelicula * pelicula ); // agrega pelicula al final de la lista enlazada
        void ordenar () ; // ordena la lista
        void calcular_rating_promedio () ;
        void mostrar_peliculas () ;
};

Director::Director(){
    head = nullptr;
    curr = nullptr;
    tail = nullptr;
    size = 0;
    nombre_director = "";
}

Director::~Director() {
    lNodo * temp;
    while (head != nullptr) {
        temp = head;
        head = head->sig;
        delete temp->val; // Liberar la memoria de la película
        delete temp;      // Liberar el nodo
    }
}

void Director::agregar_pelicula(Pelicula * pelicula){

}


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
        void eliminar_arbol(aNodo* nodo);
    public :
        Arboles () ; // constructor
        ~ Arboles () ; // destructor
        void insertar_pelicula ( Pelicula * pelicula );
        void copiar_arbol (); // hace copia de arbol 1 en arbol 2 ordenado respecto de rating
        Director * buscar_director ( string director ); // retorna arreglo de peliculas
        Pelicula * buscar_pelicula ( string pelicula ); // retorna peliculas
};

Arboles::Arboles(){
    root_1, curr_1, root_2, curr_2 = nullptr;
    size_1, size_2 = 0;
}

// Implementación del método eliminar_arbol
void Arboles::eliminar_arbol(aNodo* nodo) {
    if (nodo == nullptr) return;
    eliminar_arbol(nodo->izq);  // Eliminar subárbol izquierdo
    eliminar_arbol(nodo->der);  // Eliminar subárbol derecho
    delete nodo->val;           // Liberar memoria del Director
    delete nodo;                // Liberar el nodo
}

// Implementación del destructor
Arboles::~Arboles() {
    eliminar_arbol(root_1); // Llamar a eliminar_arbol para root_1
    eliminar_arbol(root_2); // Llamar a eliminar_arbol para root_2
}

void leerArchivo(string nombreArchivo, Arboles& arbol) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo.\n";
        return;
    }

    string linea;
    int numeroPeliculas = 0;

    // Leer la primera línea que contiene el número de películas
    if (getline(archivo, linea)) {
        numeroPeliculas = stoi(linea);
    }

    // Leer las siguientes líneas con la información de cada película
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string titulo, director, ratingStr;

        // Dividir la línea usando el delimitador ';'
        if (getline(ss, titulo, ';') &&
            getline(ss, director, ';') &&
            getline(ss, ratingStr, ';')) {
            cout << titulo << " " << director << " " << ratingStr << endl; //probandoooo
            // Crear una nueva película
            Pelicula* pelicula = new Pelicula{titulo, director, stof(ratingStr)};

            // Insertar la película en el árbol
            //arbol.insertar_pelicula(pelicula);
        }
    }

    archivo.close();  // Cerrar el archivo
}


void Arboles::insertar_pelicula(Pelicula* pelicula){
     if (root_1 == nullptr) {
        // Si el árbol está vacío, creamos un nuevo nodo raíz para el director
        aNodo* nuevo_nodo = new aNodo();
        nuevo_nodo->val = new Director();  // Crear el objeto Director
        nuevo_nodo->val->nombre_director = pelicula->director;  // Asignar el nombre del director
        nuevo_nodo->val->agregar_pelicula(pelicula);  // Agregar la película al nuevo director
        nuevo_nodo->izq = nullptr;
        nuevo_nodo->der = nullptr;
        root_1 = nuevo_nodo;
    }else {
        //busca si el director esta en el arbol
        aNodo actual = root_1;
        aNodo padre = nullptr;

        while(actual != nullptr){
            if(pelicula -> director == actual->val->nombre_director){
                //si esxiste se agrega la peli a la lista
                actual->val->agregar_pelicula(pelicula);
                return;
            }
            //sino existe movemos el nodo 
            padre = actual;
            if(pelicula->director < actual->val->nombre_director){
                actual=actual->izq;
            }else{
                actual= actual->der;
            }
        }
        //creamos si el director no existe en el arbol
        aNodo* nuevo_nodo = new aNodo();
        nuevo_nodo->val = new Director();  // Crear el objeto Director
        nuevo_nodo->val->nombre_director = pelicula->director;  // Asignar el nombre del director
        nuevo_nodo->val->agregar_pelicula(pelicula);  // Agregar la película al nuevo director
        nuevo_nodo->izq = nullptr;
        nuevo_nodo->der = nullptr;

        //se busca la posicion donde va el director

        if(pelicula->director < padre->val->nombre_director){
            padre->izq = nuevo_nodo;
        }else{
            padre -> der = nuevo_nodo;
        }

    }
}

int main(){

    Arboles arbol;

    string nombreArchivo = "Peliculas.txt";
    leerArchivo(nombreArchivo, arbol);


    
    return 0;
    
}
