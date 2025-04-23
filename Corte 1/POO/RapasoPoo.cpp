#include <iostream>

using namespace std;

class Vector{
    int* v;
    int capacity;
    int size;

public:
    //Constructor por defecto
    Vector(){
        capacity = 10; 
        size = 0;
        v = new int[capacity];
    }
    //Constructor con parametros
    Vector(int c){
        capacity = c;
        size = 0;
        v = new int[capacity];
    }
    //Destructor 
    ~Vector(){
        delete[] v;
    }
    //Funcion que permite retornar el tamaño del vector en tipo entero 
    int getSize(){
        return size;
    }
    //Funcion que permite retornar la capacidad del vector en tipo entero 
    int getCapacity(){
        return capacity;
    }
    //Funcion que garantiza el recorrido del vector desde la poscion 0 hasta size - 1, para devolver el vector. 
    int get(int i){
        if(i >= 0 && i < size){
            return v[i];
        }
    //En este caso si la posicion es invalida retorna -1
        else{
            return -1;
        }
    }
    //Corre todos los elementos desde la posicion insert una posicion a la derecha
    void  corrimientoDer(int i){
        cout <<"esto es size: "<< size << endl;
        if(size == capacity){
            resize();
        }
        for(int j = size; j > i; j--){
            v[j] = v[j-1];
        }
        size++;
        cout << "esto lo corre: " << size << endl;
        cout << "en esta pos va a estar: " << i << endl;
    }
    //Inserta el elemento d en la posicon i, luego corre a la  derecha el elemento en i y todos los elementos a la derecha de i
    void insert(int d, int i){
        corrimientoDer(i);
        v[i] = d;
    }

    void removeIn(){
        
    }

    void resize(){
        capacity *= 2;
        int* nv = new int[capacity];
        for (int i =  0; i < size; i++){
            nv[i] = v[i];
        }
        delete[] v;
        v = nv;
    }

    void add(int d){
        if(size == capacity){
            resize();
        }
        v[size++] = d;
    }

    void print(){
        for(int i = 0; i < size; i++){
            cout << v[i] <<"\t";
        }
        cout << endl;
    }
};

main(){
    Vector v(3);
    for (int i = 0; i < 3; i++){
        v.add(rand() % 100);
    }
    v.print();
    v.insert(44, 1);
    v.print();
}