
#include <iostream>
#include <ctime>  // Para srand(time(0))
#include <string>

using namespace std;


/*código para la matriz*/

// Función para crear una matriz dinámica
int** crear_mat(int f, int c) {
    int** m = new int*[f];
    for (int i = 0; i < f; i++) {
        m[i] = new int[c];
        for (int j = 0; j < c; j++) {
            m[i][j] = 0;
        }
    }
    return m;
}

// Función para destruir la matriz
void destruir_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// Función para imprimir la matriz
void print_mat(int** m, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


/*código para el arreglo*/

int* crear_arreglo(int n) {
    int* arr = new int[n];  // Crear arreglo dinámico de tamaño n
    for (int i = 0; i < n; i++) {
        arr[i] = 0;  // Inicializar con 0 (o cualquier otro valor que desees)
    }
    return arr;
}

// Función para destruir el arreglo
void destruir_arreglo(int* arr) {
    delete[] arr;  // Liberar la memoria del arreglo dinámico
}

// Función para imprimir el arreglo
void print_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

// Función para llenar el arreglo con valores
void llenar_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Introduce el valor para el elemento " << i << ": ";
        cin >> arr[i];
    }
}

//clase Venta
class Venta {
    private:
        int cliente;
        int vendedor;
        int producto;
    public:
        Venta() {
            cliente = -1; 
            vendedor = -1;
            producto = -1;
        }
        Venta(int c, int v, int p) {
            cliente = c;
            vendedor = v;
            producto = p;
        }
        
        //Getters y Setters
        int getCliente() const { 
            return cliente; 
        }
        void setCliente(int c) { 
            cliente = c; 
        }
        int getVendedor() const { 
            return vendedor; 
        }
        void setVendedor(int v) { 
            vendedor = v; 
        }
    
        int getProducto() const { 
            return producto; 
        }
        void setProducto(int p) { 
            producto = p; 
        }
    
        Venta& operator=(const Venta& f) {
            cliente = f.cliente;
            vendedor = f.vendedor;
            producto = f.producto;
            return *this;
        }
    
        string to_string() const {
            return std::to_string(cliente) + ", " + std::to_string(vendedor) + ", " + std::to_string(producto);
        }
    
        friend std::ostream& operator<<(std::ostream& os, const Venta& s) {
            return os << s.to_string();
        }
    };


// Clase nodo con plantilla Juan Felipe Poveda 
template <typename T>
class Nodo{
    private:
        T valor;
        Nodo<T>* siguiente;
    public:
        // constructor 
        Nodo(T _valor) : valor(_valor), siguiente(nullptr){}

        // Metodo setter para ajustar siguiente
        void setSiguiente(Nodo<T>* _siguiente){
            this -> siguiente = _siguiente;
        }

        // Metodo setter para ajustar valor
        void setValor(T _valor){
            this -> valor = _valor;
        }

        // Metodo getter para valor
        T getValor(){
            return valor;
        }

        // Metodo getter paar siguiente
        Nodo<T>* getSiguiente(){
            return siguiente;
        }
};



//poner aquí su código de listas con los comentarios realizados en las clases
//Juan Felipe Poveda 
template <typename T>
class Lista{
private: 
    Nodo<T>* cabeza; // Apuntador al primer nodo de la lista
    int size;
public:
    // Constructor inicializa la lista como vacía
    Lista(): cabeza(nullptr), size(0) {};
    
    // Destructor que libera la memoria de la lista
    ~Lista(){
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while(actual != nullptr){
            siguiente = actual -> getSiguiente(); // Guardamos la dirección del siguiente nodo
            delete actual; // Liberamos el nodo actual
            actual = siguiente; // Avanzamos al siguiente nodo
        }
    }
    
    // Método para insertar nodos al final de la lista Juan Felipe Poveda 
    void insertar(T _valor){
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if(cabeza == nullptr){ // Si la lista está vacía, el nuevo nodo es la cabeza
            cabeza = nuevoNodo;
        }else{
            Nodo<T>* actual = cabeza;
            while(actual -> getSiguiente()){ // Recorremos hasta el último nodo
                actual = actual -> getSiguiente();
            }
            actual -> setSiguiente(nuevoNodo); // Se enlaza el nuevo nodo al final
        }
        size ++;
    }

    // Método para insertar un nodo en una posición específica Juan Felipe Poveda 
    void insertarEnPosicion(int posicion, const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);

        if (posicion == 0) {
            nuevoNodo->setSiguiente(cabeza);
            cabeza = nuevoNodo;
            return;
        }

        Nodo<T>* actual = cabeza;
        int contador = 0;
        while (actual != nullptr && contador < (posicion - 1)) {
            actual = actual->getSiguiente();
            contador++;
        }

        if (actual == nullptr) {
            std::cout << "Posición inválida" << std::endl;
            delete nuevoNodo;
            return;
        }

        nuevoNodo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevoNodo);
    }

    // Método para eliminar un nodo por su valor  Juan Felipe Poveda 
    bool eliminar(const T& _valor){
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;
        while(actual){
            if(actual -> getValor() == _valor){
                if(anterior){
                    anterior -> setSiguiente(actual -> getSiguiente());
                }
                else{
                    cabeza = actual -> getSiguiente();
                }
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual -> getSiguiente();
        }
        return false;
    }
    
    Nodo<T>* buscarPorValor(const T& _valor) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->getValor() == _valor) {
                return actual;
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }

    int get_size() const { return size; }

    // Método para mostrar la lista Juan Felipe Poveda 
    void mostrar() const {
        Nodo<T>* actual = cabeza;
        cout << "Lista de valores: " << endl;
        while (actual != nullptr) {
            cout << actual->getValor() << endl;
            actual = actual->getSiguiente();
        }
        cout << "nullptr" << endl; // Indicamos el final de lista
    }

    Nodo<T>* get(int i) const {
        if (i >= 0 && i < size) {
            int j = 0;
            Nodo<T>* actual = cabeza;
            while (j < i) {
                actual = actual->getSiguiente();
                j++;
            }
            return actual;
        }
        return nullptr;
    }
};


// Clase Distribuidora
class Distribuidora {
private:
    Lista<Venta> ventas;
    int** matriz;
    int* arreglo;
    int nc;
    int nv;
    int np;
    int ns;

public:
    Distribuidora(int c = 100, int v = 100, int p = 100, int s = 1000): nc(c), nv(v), np(p), ns(s) {
        matriz = crear_mat(nv, np);
        arreglo = crear_arreglo(nv);
    }

    ~Distribuidora() {
        destruir_mat(matriz, nv);
        destruir_arreglo(arreglo);
    }
    
    //crear el método init_lista() Juan Felipe Poveda 

    void init_lista() {
       Venta* t;
       int c , v, p;
       for (int i = 0; i < ns; i++){
        c = rand() % nc;
        v = rand() % nv;
        p = rand() % np;
        t = new Venta(c, v, p);
        ventas.insertar(*t);
       }
       cout << "Se han generado " << ventas.get_size() << " ventas." << endl;
       ventas.mostrar();
    }

    void print() {
        ventas.mostrar();
    }
    //crear el método calcular matriz Juan Felipe Poveda 
    void calcular_matriz() {
        Nodo<Venta>* ptr = ventas.get(0);
        for (int i = 0; i < ns; i++) {
            matriz[ptr->getValor().getVendedor()][ptr->getValor().getProducto()]++;
            ptr = ptr->getSiguiente();
        }
        cout << "Matriz de libros por género: " << endl;
        print_mat(matriz, nv, np);
    }

     void generar_arreglo() {
        Nodo<Venta>* ptr = ventas.get(0);
        while (ptr != nullptr) {
            arreglo[ptr->getValor().getVendedor()]++;  // Incrementar el vendedor correspondiente en el arreglo Juan Felipe Poveda 
            ptr = ptr->getSiguiente();
        }
        cout << "Arreglo de vendedores: " << endl;
        for (int i = 0; i < nv; i++) {
        }
        print_arreglo(arreglo, nv);  // Imprimir el arreglo con los vendedores y sus ventas Juan Felipe Poveda 
    }
    


   //crear el método vendedor_con_mas_ventas_por_producto Juan Felipe Poveda 
   void vendedor_con_mas_ventas_por_producto() {
    int max_ventas = 0;
    int vendedor = -1;
    for (int i = 0; i < nv; i++) {
        int total = 0;
        for (int j = 0; j < nc; j++) {
            total += matriz[i][j];
        }
        if (total > max_ventas) {
            max_ventas = total;
            vendedor = i;
        }
        cout << "Vendedor con mas ventas: " << i << " con:  " << max_ventas << " ventas." << endl;
    }
}
    
    //crear el método calcular_promedio_ventas  Juan Felipe Poveda 
    void calcular_promedio_ventas() { //Juan Felipe Poveda 
        for (int i = 0; i < nv; i++) {
            int total = 0;
            for (int j = 0; j < nc; j++) {
                total += matriz[j][i];
            }
            double promedio = total / (double)nc;
            cout << "Promedio de ventas " << i << ": " << total << endl;
        }
    }
};

int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual Juan Felipe Poveda 
    int c = 10;
    int v = 10;
    int p = 10;
    int s = 100;
    Distribuidora dis = Distribuidora(c, v, p, s);
    dis.init_lista();
    cout << endl;
    dis.calcular_matriz();
    for (int i = 0; i < p; i++) {
        cout << "El vendedor con más ventas en el producto " << i << " es: "<< endl;
    }
    cout << "-------------datos del arreglo-------------" << endl;
    dis.generar_arreglo();
    dis.calcular_promedio_ventas();
    return 0;
}