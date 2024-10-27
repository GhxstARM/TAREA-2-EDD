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

struct tNodoAux {
    Pelicula * val ;
    tNodoAux * sig ;
    float promedio_total;
    tNodoAux(Pelicula* pelicula) : val(pelicula), sig(nullptr) {}
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
        float promedio;
        void agregar_pelicula ( Pelicula * pelicula ); // agrega pelicula al final de la lista enlazada // listo
        void ordenar () ; // ordena la lista //listo
        void calcular_rating_promedio () ; //listo
        void mostrar_peliculas () ; //listo
        void setNombre_director(const string& nombre); //listo
        string obtener_nombre(); //listo
        tNodoAux * obtenerpelis(); //listo
        void liberarpelis(tNodoAux* head_temp); //listo
};

tNodoAux* Director::obtenerpelis(){
    tNodoAux* head_temp = nullptr;
    tNodoAux* tail_temp = nullptr;
    lNodo* aux = head;
    
    while (aux != nullptr) {
        Pelicula* copia = new Pelicula(*aux->val);  // Copiar la película
        tNodoAux* nuevo_nodo = new tNodoAux(copia);
        
        if (head_temp == nullptr) {
            head_temp = tail_temp = nuevo_nodo;
        } else {
            tail_temp->sig = nuevo_nodo;
            tail_temp = nuevo_nodo;
        }
        
        aux = aux->sig;
    }
    return head_temp;
}

void Director::liberarpelis(tNodoAux* head_temp) {
    if(head_temp == nullptr) return;
    tNodoAux* actual = head_temp;
    while (actual != nullptr) {
        tNodoAux* temp = actual;
        actual = actual->sig;
        delete temp->val;  // Liberar cada película
        delete temp;       // Liberar el nodo de tNodoAux
    }
    actual = nullptr;
}

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
        cout<< aux->val->nombre << " / " << aux->val->rating <<endl;
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

    // cout<<size<<"-"<<aux->val->director<<endl;

    while(aux != nullptr){
        sumar += aux->val->rating;
        c += 1;
        aux = aux->sig;
    }
    if(c > 0){
        promedio = sumar/c;
    }else{
        promedio = 0;
    }
    
    // cout<<promedio<<endl;

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
        int cantidadpelis;
        void insertar_pelicula ( Pelicula * pelicula ); //listo
        void copiar_arbol (); // hace copia de arbol 1 en arbol 2 ordenado respecto de rating //listo
        Director * buscar_director ( string director ); // retorna arreglo de peliculas //listo
        Pelicula * buscar_pelicula ( string pelicula ); // retorna peliculas
        void mostrar(); //listo
        void ayuda(aNodo * nodo); //listo
        void copiar_arbol_aux(aNodo * nodo); //listo
        void insertar_por_promedio(aNodo*& root, Director* director); //listo
        void mostrardirector(string nombre);
        void mostrarpeli(string pelicula);
        Pelicula* buscar_pelicula_recursivo(aNodo* nodo, string pelicula);

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

    arbol.cantidadpelis = numeroPeliculas;
    
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

void Arboles::copiar_arbol() {
    root_2 = nullptr; // Asegúrate de que root_2 está vacío antes de copiar
    copiar_arbol_aux(root_1);
}

void Arboles::copiar_arbol_aux(aNodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    // Procesa el nodo actual antes de sus hijos (preorden)
    Director* nuevo_director = new Director();
    nuevo_director->setNombre_director(nodo->val->obtener_nombre());

    // Copiar todas las películas del director original al nuevo
    tNodoAux* peliculas = nodo->val->obtenerpelis();
    tNodoAux* actual = peliculas;

    while (actual != nullptr) {
        Pelicula* nueva_pelicula = new Pelicula(*actual->val); // Suponiendo que tienes un constructor de copia
        nuevo_director->agregar_pelicula(nueva_pelicula);
        actual = actual->sig;
    }

    // Liberar la memoria de la lista temporal
    nodo->val->liberarpelis(peliculas);  // Liberar las películas copiadas

    // Calcular el rating promedio para el nuevo director y agregarlo a `root_2`
    nuevo_director->calcular_rating_promedio();
    insertar_por_promedio(root_2, nuevo_director);

    // Llamada recursiva en preorden
    copiar_arbol_aux(nodo->izq);
    copiar_arbol_aux(nodo->der);
}


void Arboles::insertar_por_promedio(aNodo*& root, Director* director) {
    if (root == nullptr) {
        root = new aNodo();
        root->val = director;
        root->izq = nullptr;
        root->der = nullptr;
    } else {
        if (director->promedio < root->val->promedio) {
            insertar_por_promedio(root->izq, director);
        } else {
            insertar_por_promedio(root->der, director);
        }
    }
}

Director * Arboles::buscar_director(string director){
    aNodo* aux = root_1;
    if(aux == nullptr) return nullptr;
    while(aux != nullptr){
        if (aux->val->obtener_nombre() == director) {
            return aux->val; // Retorna el director encontrado
        }
        
        // Si el nombre es menor, se mueve a la izquierda; si es mayor, a la derecha
        if (director < aux->val->obtener_nombre()) {
            aux = aux->izq; // Moverse al subárbol izquierdo
        } else {
            aux = aux->der; // Moverse al subárbol derecho
        }
    }
    return nullptr;
}

void Arboles::mostrardirector(string nombre) {
    // Busca el director por su nombre
    Director* directorEncontrado = buscar_director(nombre);
    
    // Verifica si se encontró el director
    if (directorEncontrado != nullptr) {
        directorEncontrado->mostrar_peliculas(); // Muestra las películas del director
    } else {
        return;
    }
}

Pelicula* Arboles::buscar_pelicula(string pelicula) {
    aNodo* aux = root_1;
    return buscar_pelicula_recursivo(aux, pelicula);
}

Pelicula* Arboles::buscar_pelicula_recursivo(aNodo* aux, string pelicula) {
    if (aux == nullptr) return nullptr;

    Director* directoractual = aux->val;
    tNodoAux* listapelis = directoractual->obtenerpelis();
    tNodoAux* actual = listapelis;

    while(listapelis != nullptr){
        listapelis = listapelis->sig;
    }

    // Recorremos la lista de películas del director
    while (actual != nullptr) {
        if (actual->val->nombre == pelicula) {
            Pelicula* encontrada = actual->val;
            directoractual->liberarpelis(listapelis);  // Liberar lista antes de devolver
            return encontrada;  // Retornar la película encontrada
        }
        actual = actual->sig;
    }

    // Liberar lista temporal de películas al terminar de revisar este director
    directoractual->liberarpelis(listapelis);

    // Continuar búsqueda en el subárbol izquierdo
    Pelicula* resultado_izq = buscar_pelicula_recursivo(aux->izq, pelicula);
    if (resultado_izq != nullptr) return resultado_izq;  // Si se encontró en el lado izquierdo

    // Continuar búsqueda en el subárbol derecho
    Pelicula* resultado_der = buscar_pelicula_recursivo(aux->der, pelicula);
    if(resultado_der != nullptr) return resultado_der;

    directoractual->liberarpelis(listapelis);
    return nullptr;  // Devuelve el resultado del lado derecho (o nullptr si no se encontró)
}


void Arboles::mostrarpeli(string pelicula){
    Pelicula * peliaux = buscar_pelicula(pelicula);
    if (peliaux != nullptr) {
        cout << peliaux->nombre << " / " << peliaux->director << " / " << peliaux->rating << endl;
    } else {
        return;
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
            arbol.mostrardirector(director);
            
        } else if (instruccion.substr(0, 3) == "sm ") {
            // Buscar película
            string pelicula = instruccion.substr(3);
            cout << pelicula << endl;
            arbol.mostrarpeli(pelicula);

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
            continue;
        }
    }
    
    return 0;
    
}
