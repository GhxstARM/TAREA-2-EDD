#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Pila {
private:
    struct pNodo {
        string valor;
        pNodo* siguiente;
    };
    
    pNodo* cima;  // Puntero al nodo en el tope de la pila
    int sizes; // Para llevar la cuenta de los elementos en la pila

public:
/* ****
* Constructor Pila
******
* Resumen: Inicializa una pila vacía, configurando el puntero de la cima a `nullptr` 
*          y el tamaño de la pila (`sizes`) a 0.
******
* Input:
* No tiene
******
* Returns:
* No retorna ningún valor.
**** */
    Pila() : cima(nullptr), sizes(0) {}

/* ****
* Destructor ~Pila
******
* Resumen: Libera la memoria de todos los nodos en la pila llamando a la función `clear()`.
******
* Input:
* No tiene.
******
* Returns:
* No retorna ningún valor.
**** */
    ~Pila() { clear(); }

/* ****
* void clear
******
* Resumen: Vacía la pila eliminando todos los nodos y liberando su memoria.
******
* Input:
* No tiene.
******
* Returns:
* No retorna ningún valor.
**** */
    void clear() {
        while (!estaVacia()) {
            pop();
        }
    }

/* ****
* void push
******
* Resumen: Agrega un nuevo nodo al tope de la pila con el valor proporcionado.
******
* Input:
* string item : El valor de tipo string que se almacenará en el nuevo nodo de la pila.
******
* Returns:
* no retorna ningún valor.
**** */
    void push(string item) {
        pNodo* nuevoNodo = new pNodo();
        nuevoNodo->valor = item;
        nuevoNodo->siguiente = cima;
        cima = nuevoNodo;
        sizes++;

    }


/* ****
* void pop
******
* Resumen: Elimina el nodo que está en el tope de la pila y libera su memoria.
******
* Input:
* 
******
* Returns:
* No retorna ningún valor.
* Muestra un mensaje de error si la pila está vacía. 
**** */
    void pop() {
        if (estaVacia()) {
            std::cerr << "Error: la pila está vacía." << std::endl;
            return;
        }
        pNodo* nodoAEliminar = cima;
        cima = cima->siguiente;
        delete nodoAEliminar;
        sizes--;
    }


/* ****
* String topValue
******
* Resumen: Retorna el valor almacenado en el nodo en el tope de la pila.
******
* Input:
* No tiene.
******
* Returns:
* string, el valor en el tope de la pila. 
* Muestra un mensaje de error y retorna una cadena vacía si la pila está vacía.
**** */

    string topValue() const {
        if (estaVacia()) {
            cerr << "la pila está vacía." << endl; 
        }
        return cima->valor;
    }


/* ****
* int size
******
* Devuelve el tamaño actual de la pila.
******
* Input :
* no tiene
******
* Returns :
* int , El tamaño de la pila.
**** */

    int size(){
        return sizes;
    }


/* ****
* bool estaVacia
******
* Revisa si la estructura está vacía.
******
* Input :
* no tiene.
******
* Returns :
* bool , `true` si la pila está vacía, `false` en caso contrario.
**** */
    bool estaVacia() const {
        return cima == nullptr;
    }
};

struct Pelicula {
    string nombre ;
    string director ;
    float rating ;
};

class tNodoAux {
private:
    Pelicula* val;
    tNodoAux* sig;
    tNodoAux* curr;
    tNodoAux* head;
    float promedio_total;

public:
    
    tNodoAux(Pelicula* pelicula, float promedio = 0.0f) 
        : val(pelicula), sig(nullptr), promedio_total(promedio) {}

    
    ~tNodoAux(){
        delete val;
    }

   /* ****
* Pelicula* getVal
******
* Devuelve un puntero a la película almacenada en el nodo.
******
* Input :
* No tiene.
******
* Returns :
* Pelicula* : Un puntero al objeto Pelicula almacenado en el nodo.
**** */

    Pelicula* getVal() const { return val; }


/* ****
* void setVal
******
* Establece el valor de la película almacenada en el nodo.
******
* Input :
* Pelicula* pelicula : Un puntero al objeto Pelicula que se desea almacenar en el nodo.
******
* Returns :
* No devueleve un valor
**** */
    void setVal(Pelicula* pelicula) { val = pelicula; }

/* ****
* tNodoAux* getSig
******
* Obtiene el puntero al siguiente nodo en la lista enlazada.
******
* Input :
* no tiene.
******
* Returns :
* tNodoAux* : Un puntero al siguiente nodo de tipo tNodoAux.
**** */

    tNodoAux* getSig() const { return sig; }


/* ****
* void setSig
******
* Establece el puntero al siguiente nodo en la lista enlazada.
******
* input:
* tNodoAux* siguiente : Un puntero al siguiente nodo de tipo tNodoAux que se desea establecer.
******
* Returns :
* No devueleve un valor
**** */
    void setSig(tNodoAux* siguiente) { sig = siguiente; }


/* ****
* tNodoAux* getCurr
******
* Obtiene el puntero al nodo actual en la lista enlazada.
******
* Input :
* no tiene.
******
* Retorna :
* tNodoAux* : Un puntero al nodo actual de tipo tNodoAux. 
* Si el puntero es nulo, significa que no hay un nodo actual definido.

**** */
    tNodoAux* getCurr() const {return curr;}


/* ****
* void setCurr
******
* Establece el puntero al nodo actual en la lista enlazada.
******
* input :
* tNodoAux* nodo : Un puntero al nodo de tipo tNodoAux que se establecerá como el nodo actual.
******
* Returns :
* No devueleve un valor
**** */
    void setCurr(tNodoAux* nodo) {curr = nodo;}


/* ****
* tNodoAux* getHead
******
* Resumen:
* Obtiene el puntero al primer nodo de la lista enlazada.
******
* Input :
* Ninguno
******
* Returns :
* tNodoAux*, Puntero al nodo cabeza de la lista enlazada.
**** */
    tNodoAux* getHead() const {return head;}


/* ****
* void setHead
******
* Resumen:
* Establece el puntero al primer nodo de la lista enlazada.
******
* Input :
* tNodoAux* nodo : Puntero al nodo que se establecerá como cabeza de la lista.
******
* Returns :
* Ninguno.
**** */
    void setHead(tNodoAux* nodo) {head = nodo;}


/* ****
* float getPromedioTotal
******
* Resumen Función
* Devuelve el promedio total de las películas.
******
* Input :
* Ninguno.
******
* Returns :
* float : El promedio total de las películas.
**** */
    float getPromedioTotal() const { return promedio_total; }

/* ****
* void setPromedioTotal
******
* Resumen Función
* Establece el promedio total de las películas.
******
* Input :
* float promedio : El nuevo promedio total a establecer.
******
* Returns :
* Ninguno.
**** */
    void setPromedioTotal(float promedio) { promedio_total = promedio; }
    
/* ****
* void moveToStart
******
* Resumen Función
* Mueve el puntero `curr` al inicio de la lista enlazada.
******
* Input :
* Ninguno.
******
* Returns :
* Ninguno.
**** */
    void moveToStart() { curr = head; } 
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
        void agregar_pelicula ( Pelicula * pelicula ); // agrega pelicula al final de la lista enlazada 
        void ordenar () ; // ordena la lista 
        void calcular_rating_promedio () ;
        void mostrar_peliculas () ; 
        void setNombre_director(const string& nombre); 
        string obtener_nombre(); 
        tNodoAux * obtenerpelis(); 
        void liberarpelis(tNodoAux* head_temp);
};



/* ****
* tNodoAux* obtenerpelis
******
* Crea una copia de la lista de películas asociadas al director y devuelve el puntero al primer nodo de la nueva lista.
******
* Input :
* no tiene
******
* Returns :
* tNodoAux* , Un puntero al primer nodo de la nueva lista de películas.
**** */

tNodoAux* Director::obtenerpelis() {

    tNodoAux* head_temp = nullptr;
    tNodoAux* tail_temp = nullptr;
    lNodo* aux = head;
    
    while (aux != nullptr) {
        Pelicula* copia = new Pelicula;  
        *copia = *aux->val;

        tNodoAux* nuevo_nodo = new tNodoAux(copia); 

        if (head_temp == nullptr) {
            head_temp = tail_temp = nuevo_nodo;
        } else {
            tail_temp->setSig(nuevo_nodo);  
            tail_temp = nuevo_nodo;
        }
        
        aux = aux->sig;
    }

    if (head_temp != nullptr) {
        head_temp->moveToStart(); 
    }

    return head_temp;
}


/* ****
* void liberarpelis
******
* Libera la memoria ocupada por la lista de nodos de películas.
******
* Input :
* tNodoAux* lista : Puntero al primer nodo de la lista de películas a liberar.
******
* Returns :
* no devuelve ningún valor.
**** */
void Director::liberarpelis(tNodoAux* lista) {
    if (lista == nullptr) return;
    
    tNodoAux* actual = lista;

    while (actual != nullptr) {
        tNodoAux* temp = actual;
        actual = actual->getSig(); 
        delete temp;  
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
        delete temp->val; 
        delete temp;      
    }
}


/* ****
* void agregar_pelicula
******
* Agrega una nueva película a la lista de películas del director.
******
* Input :
* Pelicula* pelicula : Puntero a la película que se desea agregar a la lista.
******
* Returns :
* no devuelve ningún valor.
**** */

void Director::agregar_pelicula(Pelicula * pelicula){
    lNodo *aux= new lNodo();
    aux->val=pelicula;
    aux->sig = nullptr;

    if(head == nullptr){
        head = tail = curr = aux;

    }else{
        tail->sig = aux;
        tail = aux;
    }
    size++;
}


/* ****
* void ordenar
******
* Ordena la lista de películas alfabéticamente por el nombre de cada película.
******
* Input :
* no tiene
******
* Returns :
* no devuelve ningún valor.
**** */

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


/* ****
* void mostrar_peliculas
******
* Muestra en la consola los nombres y ratings de las películas de un director.
******
* Input :
* no tiene
******
* Returns :
* no devuelve ningún valor.
**** */

void Director::mostrar_peliculas(){
    lNodo *aux= head;
    while(aux != nullptr){
        cout<< aux->val->nombre << " / " << aux->val->rating <<endl;
        aux = aux->sig;
    }
}


/* ****
* void setNombre_director
******
* Establece el nombre del director.
******
* Input :
* const string& nombre : parametro por referencia a un string que contiene el nombre del director.
******
* Returns :
* no devuelve ningún valor.
**** */
void Director::setNombre_director(const string& nombre){
    nombre_director = nombre;
}


/* ****
* string obtener_nombre
******
* Devuelve el nombre del director.
******
* Input :
* no tiene.
******
* Returns :
* string , El nombre del director almacenado en "nombre_director".
**** */
string Director::obtener_nombre(){
    return nombre_director;
}


/* ****
* void calcular_rating_promedio
******
* Calcula el rating promedio de las películas del director.
******
* Input :
* no tiene.
******
* Returns :
* no devuelve ningún valor.
**** */
void Director::calcular_rating_promedio(){
    lNodo *aux= head;
    float sumar = 0;
    promedio  = 0;
    int c = 0;
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
        void insertar_pelicula ( Pelicula * pelicula ); 
        void copiar_arbol (); // hace copia de arbol 1 en arbol 2 ordenado respecto de rating 
        Director * buscar_director ( string director ); // retorna arreglo de peliculas 
        Pelicula * buscar_pelicula ( string pelicula ); // retorna peliculas
        void mejores_directores ( int n); 
        void peores_directores ( int n );
        void copiar_arbol_aux(aNodo * nodo); 
        void insertar_por_promedio(aNodo*& root, Director* director); 
        void mostrardirector(string nombre);
        void mostrarpeli(string pelicula);
        Pelicula* buscar_pelicula_recursivo(aNodo* nodo, string pelicula);
        int contarNodos();
        void inordenYGuardarEnPila(aNodo* nodo, Pila * p);


};


Arboles::Arboles(){
    root_1 = nullptr;
    curr_1 = nullptr;
    root_2 = nullptr;
    curr_2 = nullptr;
    size_1 = 0;
    size_2 = 0;
}


/* ****
* void eliminar_arbol
******
* Elimina un árbol binario, liberando la memoria ocupada por cada nodo y su contenido.
******
* Input :
* aNodo* nodo : Puntero al nodo raíz del árbol a eliminar.
******
* Returns :
* no devuelve ningún valor.
**** */

void Arboles::eliminar_arbol(aNodo* nodo) {
    if (nodo == nullptr) return;
    eliminar_arbol(nodo->izq); 
    eliminar_arbol(nodo->der);  
    delete nodo->val;          
    delete nodo;               
}


Arboles::~Arboles() {
    eliminar_arbol(root_1); 
    eliminar_arbol(root_2); 
}


/* ****
* void leerArchivo
******
* Lee el archivo Peliculas.txt que contiene información de películas y las inserta en un árbol binario de busqueda.
******
* Input :
* string nombreArchivo : Nombre del archivo que se va a leer.
* Arboles& arbol : Referencia al árbol donde se insertarán las películas leídas del archivo.
******
* Returns :
* no devuelve ningún valor.
**** */
void leerArchivo(string nombreArchivo, Arboles& arbol) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo.\n";
        return;
    }

    string linea;
    int numeroPeliculas = 0;

    
    if (getline(archivo, linea)) {
        numeroPeliculas = stoi(linea);
    }

    arbol.cantidadpelis = numeroPeliculas;
    
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string titulo, director, ratingStr;

        
        if (getline(ss, titulo, ';') &&
            getline(ss, director, ';') &&
            getline(ss, ratingStr, ';')) {

            Pelicula* pelicula = new Pelicula{titulo, director, stof(ratingStr)};

            
            arbol.insertar_pelicula(pelicula);
        }
    }

    archivo.close();  
}


/* ****
* void insertar_pelicula
******
* Inserta una película en el árbol de directores. Si el director ya existe, se agrega la película a su lista; si no, se crea un nuevo nodo para el director.
******
* Input :
* Pelicula* pelicula : Puntero a la película que se desea insertar en el árbol.
******
* Returns :
* no devuelve ningún valor.
**** */
void Arboles::insertar_pelicula(Pelicula* pelicula){
    if (root_1 == nullptr) {
        aNodo* nuevo_nodo = new aNodo();
        nuevo_nodo->val = new Director();  
        nuevo_nodo->val->setNombre_director(pelicula->director);  
        nuevo_nodo->val->agregar_pelicula(pelicula);  
        nuevo_nodo->izq = nullptr;
        nuevo_nodo->der = nullptr;
        root_1 = nuevo_nodo;
        size_1++;
    }else {
        aNodo* actual = root_1;
        aNodo* padre = nullptr;

        while(actual != nullptr){
            if(pelicula -> director == actual->val->obtener_nombre()){
                actual->val->agregar_pelicula(pelicula);
                return;
            }
             
            padre = actual;
            if(pelicula->director < actual->val->obtener_nombre()){
                actual=actual->izq;
            }else{
                actual= actual->der;
            }
        }
        aNodo* nuevo_nodo = new aNodo();
        nuevo_nodo->val = new Director();  
        nuevo_nodo->val->setNombre_director(pelicula->director);  
        nuevo_nodo->val->agregar_pelicula(pelicula);  
        nuevo_nodo->izq = nullptr;
        nuevo_nodo->der = nullptr;


        if(pelicula->director < padre->val->obtener_nombre()){
            padre->izq = nuevo_nodo;
            size_1++;
        }else{
            padre -> der = nuevo_nodo;
            size_1++;
        }
    }
}


/* ****
* void copiar_arbol
******
* Copia el árbol de directores y películas, creando un nuevo árbol.
******
* Input :
* no tiene.
******
* Returns :
* no devuelve ningún valor.
**** */
void Arboles::copiar_arbol() {
    root_2 = nullptr; 
    copiar_arbol_aux(root_1);
}


/* ****
* void copiar_arbol_aux
******
* Función auxiliar que copia recursivamente un árbol de nodos, creando nuevos directores y copiando sus películas.
******
* Input :
* aNodo* nodo : Puntero al nodo actual que se está copiando.
******
* Returns :
* no devuelve ningún valor.
**** */

void Arboles::copiar_arbol_aux(aNodo* nodo) {
    if (nodo == nullptr) {
        return;
    }
    Director* nuevo_director = new Director();
    nuevo_director->setNombre_director(nodo->val->obtener_nombre());

    
    tNodoAux* peliculas = nodo->val->obtenerpelis();
    tNodoAux* actual = peliculas;

    while (actual != nullptr) {
        Pelicula* nueva_pelicula = new Pelicula(*actual->getVal()); 
        nuevo_director->agregar_pelicula(nueva_pelicula);
        actual = actual->getSig();
    }

    
    nodo->val->liberarpelis(peliculas);  

    
    nuevo_director->calcular_rating_promedio();
    insertar_por_promedio(root_2, nuevo_director);


    copiar_arbol_aux(nodo->izq);
    copiar_arbol_aux(nodo->der);
}


/* ****
* void insertar_por_promedio
******
* Inserta un nuevo director en el árbol basado en su rating promedio. Si el árbol está vacío, crea un nuevo nodo; de lo contrario, lo inserta en la posición correspondiente.
******
* Input :
* aNodo*& root : Referencia al puntero del nodo raíz del árbol en el que se va a insertar el director.
* Director* director : Puntero al director que se desea insertar en el árbol.
******
* Returns :
* no devuelve ningún valor.
**** */

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


/* ****
* Director* buscar_director
******
* Busca un director en el árbol de directores dado su nombre. 
******
* Input :
* string director : El nombre del director que se desea buscar en el árbol.
******
* Returns :
* Director*,  un arreglo de peliculas del director encontrado o nullptr si no se encuentra el director.
**** */
Director * Arboles::buscar_director( string director){

    aNodo* aux = root_1;
    if(aux == nullptr) return nullptr;
    while(aux != nullptr){
        if (aux->val->obtener_nombre() == director) {
            return aux->val; 
        }
        if (director < aux->val->obtener_nombre()) {
            aux = aux->izq; 
        } 
        if(director > aux->val->obtener_nombre()) {
            aux = aux->der; 
        }
    }
    return nullptr;
}


/* ****
* void mostrardirector
******
* Busca un director en el árbol por su nombre y muestra las películas asociadas a él si se encuentra.
******
* Input :
* string nombre : El nombre del director cuyas películas se desean mostrar.
******
* Returns :
* no devuelve ningún valor.
**** */
void Arboles::mostrardirector(string nombre) {
    
    Director* directorEncontrado = buscar_director(nombre);

    if (directorEncontrado != nullptr) {
        
        directorEncontrado->mostrar_peliculas(); 
    } else {
        return;
    }
}


/* ****
* Pelicula* buscar_pelicula
******
* Busca una película en el árbol de directores utilizando el nombre de la película.
******
* Input :
* string pelicula : El nombre de la película que se desea buscar en el árbol.
******
* Returns :
* Pelicula*, puntero a la película encontrada o nullptr si no se encuentra.
**** */
Pelicula* Arboles::buscar_pelicula(string pelicula) {
    aNodo* aux = root_1;
    return buscar_pelicula_recursivo(aux, pelicula);
}


/* ****
* Pelicula* buscar_pelicula_recursivo
******
* funcion auxiliar de la funcion buscar_pelicula, que busca recursivamente una película en el árbol de directores y sus listas de películas
******
* Input :
* aNodo* aux : Puntero al nodo actual del árbol en el que se está buscando.
* string pelicula : El nombre de la película que se desea buscar.
******
* Returns :
* Pelicula*, puntero a la película encontrada o nullptr si no se encuentra.
**** */

Pelicula* Arboles::buscar_pelicula_recursivo(aNodo* aux, string pelicula) {
    if (aux == nullptr) return nullptr;

    Director* directoractual = aux->val;
    tNodoAux* listapelis = directoractual->obtenerpelis();
    listapelis->moveToStart();
    tNodoAux* actual = listapelis;


    if(listapelis == nullptr){
        listapelis->getSig();
        
        while (actual != nullptr) {
            if (actual->getVal()->nombre == pelicula) {
                Pelicula* encontrada = actual->getVal();
                directoractual->liberarpelis(listapelis);  
                return encontrada;  
            }
            actual = actual->getSig();
        }
    }else{
        while (actual != nullptr) {
            if (actual->getVal()->nombre == pelicula) {
                Pelicula* encontrada = actual->getVal();
                directoractual->liberarpelis(listapelis);  
                return encontrada;  
            }
            actual = actual->getSig();
        }
    }

    

    
    directoractual->liberarpelis(listapelis);

   
    Pelicula* resultado_izq = buscar_pelicula_recursivo(aux->izq, pelicula);
    if (resultado_izq != nullptr) return resultado_izq;  

    
    Pelicula* resultado_der = buscar_pelicula_recursivo(aux->der, pelicula);
    if(resultado_der != nullptr) return resultado_der;

    return nullptr;  
}

/* ****
* void mostrarpeli
******
* Muestra la información de una película específica buscándola en el árbol de directores.
******
* Input :
* string pelicula : El nombre de la película que se desea mostrar.
******
* Returns :
* no retorna ningún valor.
**** */
void Arboles::mostrarpeli(string pelicula){
    Pelicula * peliaux = buscar_pelicula(pelicula);
    if (peliaux != nullptr) {
        cout << peliaux->nombre << " / " << peliaux->director << " / " << peliaux->rating << endl;
    } else {
        return;
    }
}



/* ****
* void mejores_directores
******
* Muestra los nombres de los mejores directores almacenados en el árbol, basado en su rating promedio.
******
* Input :
* int n : Número de directores a mostrar.
******
* Returns :
* no retorna ningún valor.
**** */
void Arboles::mejores_directores(int n){
    Pila * pila= new Pila();
    inordenYGuardarEnPila(root_2, pila);
    for(int i=1;i<=n;i++){
        cout<<"("<<i<<")"<<pila->topValue()<<endl;
        pila->pop();
    }
    delete pila;


}


/* ****
* void peores_directores
******
* Muestra los nombres de los peores directores almacenados en el árbol, basado en su rating promedio.
******
* Input :
* int n : Número de directores a mostrar.
******
* Returns :
*no retorna ningún valor.
**** */
void Arboles::peores_directores(int n){
    Pila * pila1= new Pila();
    Pila * pila2= new Pila();
    
    inordenYGuardarEnPila(root_2, pila1);
    while(pila1->size()>0){
        pila2->push(pila1->topValue());
        pila1->pop();
    }
    for(int i=0;i<n;i++){
        cout<<"("<<size_1-i<<")"<<pila2->topValue()<<endl;
        pila2->pop();
    }

    delete pila1;
    delete pila2;

}


/* ****
* void inordenYGuardarEnPila
******
* Realiza un recorrido en orden del árbol y guarda los nombres de los directores en una pila.
******
* Input :
* aNodo* nodo : El nodo actual del árbol que se está procesando.
* Pila *p : Puntero a la pila donde se almacenarán los nombres de los directores.
******
* Returns :
*no retorna ningún valor.
**** */

void Arboles::inordenYGuardarEnPila(aNodo* nodo, Pila *p) {
    if (nodo == nullptr) return;
    inordenYGuardarEnPila(nodo->izq, p ); 
    p->push(nodo->val->obtener_nombre()); 
    inordenYGuardarEnPila(nodo->der, p); 
}

int main(){

    Arboles arbol;

    string nombreArchivo = "Peliculas.txt";
    leerArchivo(nombreArchivo, arbol);

    string instruccion;
    arbol.copiar_arbol();

    while (true) {
        cout << "Ingrese un comando: ";
        getline(cin, instruccion);

        if (instruccion == "e") {
            break;
        } else if (instruccion.substr(0, 3) == "sd ") {
            
            string director = instruccion.substr(3);
            
            arbol.mostrardirector(director);
            
        } else if (instruccion.substr(0, 3) == "sm ") {
            
            string pelicula = instruccion.substr(3);
            
            arbol.mostrarpeli(pelicula);

        } else if (instruccion.substr(0, 3) == "br ") {
            
            int n = stoi(instruccion.substr(3));
            arbol.mejores_directores(n);
        } else if (instruccion.substr(0, 3) == "wr ") {
            
            int n = stoi(instruccion.substr(3));
            arbol.peores_directores(n);
        }else {
            continue;
        }
    }
    
    return 0;
    
}
