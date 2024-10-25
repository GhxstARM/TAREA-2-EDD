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
        float promedio;


    public :
        Director (); // constructor
        ~ Director () ; // destructor
        void agregar_pelicula ( Pelicula * pelicula ); // agrega pelicula al final de la lista enlazada
        void ordenar () ; // ordena la lista
        void calcular_rating_promedio () ;
        void mostrar_peliculas () ;
        void setNombre_director(const string& nombre); //lista
        string obtener_nombre(); //lista
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
    lNodo *aux= new lNodo();
    aux->val=pelicula;
    aux->sig = nullptr;

    if(head ==nullptr){
        head = tail = curr = aux;

    }else{
        tail->sig = aux;
        tail = aux;
    }
    size++;
}

void Director::ordenar(){
    lNodo *aux1= head;
    lNodo *aux2 = nullptr;
    Pelicula *auxPelicula;


    while(aux1 != nullptr){
        aux2= aux1->sig;
        while(aux2 != nullptr){
            if(aux1->val->nombre > aux2->val->nombre){
                auxPelicula = aux2->val;
                aux2->val->nombre = aux1->val->nombre;
                aux1->val = auxPelicula;
            }
            aux1 = aux1->sig;

        }

        aux1 = aux1->sig;


    }
}

void Director::mostrar_peliculas(){
    lNodo *aux= head;
    while(aux != nullptr){
        cout<< aux->val->nombre<<endl;
        aux = aux->sig;
    }
}

void Director::setNombre_director(const string& nombre){
    nombre_director = nombre;
}

string Director::obtener_nombre(){
    return nombre_director;
}

void Director::calcular_rating_promedio(){
    lNodo *aux= head;
    float sumar = 0;
    promedio  = 0;
    int c = 0;

    cout<<size<<"-"<<aux->val->director<<endl;

    while(aux != nullptr){
        sumar += aux->val->rating;
        c += 1;
        aux = aux->sig;
    }
    promedio = sumar/c;
    cout<<promedio<<endl;
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
        void mostrar();
        void ayuda(aNodo * nodo);
};

Arboles::Arboles(){
    root_1 = nullptr;
    curr_1 = nullptr;
    root_2 = nullptr;
    curr_2 = nullptr;
    size_1 = 0;
    size_2 = 0;
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
            //cout << titulo << " " << director << " " << ratingStr << endl; //probandoooo
            // Crear una nueva película
            Pelicula* pelicula = new Pelicula{titulo, director, stof(ratingStr)};

            // Insertar la película en el árbol
            arbol.insertar_pelicula(pelicula);
        }
    }

    archivo.close();  // Cerrar el archivo
}


void Arboles::insertar_pelicula(Pelicula* pelicula){
    if (root_1 == nullptr) {
        // Si el árbol está vacío, creamos un nuevo nodo raíz para el director
        aNodo* nuevo_nodo = new aNodo();
        nuevo_nodo->val = new Director();  // Crear el objeto Director
        nuevo_nodo->val->setNombre_director(pelicula->director);  // Asignar el nombre del director
        nuevo_nodo->val->agregar_pelicula(pelicula);  // Agregar la película al nuevo director
        nuevo_nodo->izq = nullptr;
        nuevo_nodo->der = nullptr;
        root_1 = nuevo_nodo;
    }else {
        //busca si el director esta en el arbol
        aNodo* actual = root_1;
        aNodo* padre = nullptr;

        while(actual != nullptr){
            if(pelicula -> director == actual->val->obtener_nombre()){
                //si esxiste se agrega la peli a la lista
                actual->val->agregar_pelicula(pelicula);
                return;
            }
            //sino existe movemos el nodo 
            padre = actual;
            if(pelicula->director < actual->val->obtener_nombre()){
                actual=actual->izq;
            }else{
                actual= actual->der;
            }
        }
        //creamos si el director no existe en el arbol
        aNodo* nuevo_nodo = new aNodo();
        nuevo_nodo->val = new Director();  // Crear el objeto Director
        nuevo_nodo->val->setNombre_director(pelicula->director);  // Asignar el nombre del director
        nuevo_nodo->val->agregar_pelicula(pelicula);  // Agregar la película al nuevo director
        nuevo_nodo->izq = nullptr;
        nuevo_nodo->der = nullptr;

        //se busca la posicion donde va el director

        if(pelicula->director < padre->val->obtener_nombre()){
            padre->izq = nuevo_nodo;
        }else{
            padre -> der = nuevo_nodo;
        }
    }
}

void Arboles::ayuda(aNodo* nodo) {
    if (nodo != nullptr) {
        // Mostrar el nombre del director
        nodo->val->calcular_rating_promedio();
        cout << nodo->val->obtener_nombre() << endl;

        // Llamar recursivamente solo si los hijos no son nullptr
        if (nodo->izq != nullptr) {
            ayuda(nodo->izq);
        }
        if (nodo->der != nullptr) {
            ayuda(nodo->der);
        }
    }
}

void Arboles::mostrar() {
    aNodo* aux = root_1;
    if (aux != nullptr) {
        aux->val->calcular_rating_promedio();
        cout << aux->val->obtener_nombre()<<endl;
        // Utilizamos la función `ayuda` para manejar la recursión
        ayuda(aux->izq);
        ayuda(aux->der);
    }
}

int main(){

    Arboles arbol;

    string nombreArchivo = "Peliculas.txt";
    leerArchivo(nombreArchivo, arbol);

    string instruccion;

    while (true) {
        cout << "Ingrese un comando: ";
        getline(cin, instruccion);

        if (instruccion == "e") {
            break; // Terminar ejecución
        } else if (instruccion.substr(0, 3) == "sd ") {
            // Buscar director
            string director = instruccion.substr(3);
            cout << director << endl;
            
        } else if (instruccion.substr(0, 3) == "sm ") {
            // Buscar película
            string pelicula = instruccion.substr(3);
            cout << pelicula << endl;
        } else if (instruccion.substr(0, 3) == "br ") {
            // Mostrar mejores directores
            int n = stoi(instruccion.substr(3));
            cout << n << endl;
        } else if (instruccion.substr(0, 3) == "wr ") {
            // Mostrar peores directores
            int n = stoi(instruccion.substr(3));
            cout << n << endl;
        } else if(instruccion == "mo"){
            arbol.mostrar();
        }else {
            cout << "Comando no reconocido." << endl;
        }
    }

    
    return 0;
    
}
