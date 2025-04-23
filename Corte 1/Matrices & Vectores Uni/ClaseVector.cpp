#include <iostream>
#include <vector>
using namespace std;

int main()
{
    //declarar variables de tipo vector
    vector<int> v1;  //crea un vector vacio de tipo entero
    vector<string> v2; //crea un vector vacio de tipo string
    
    //* ¿qué permite push_back ?: Sirve para almacenar elementos en un vector
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(40);
    v2.push_back("Ana");
    v2.push_back("Juan");
    
    //* ¿qué permite size ? : Motrar cuantos elementos estan contenidos dentro de los vectores
    cout << "El vector v1 tiene: " << v1.size() << " elementos" << endl; 
    cout << "El vector v2 tiene: " << v2.size() << " elementos" << endl; 
    
    //¿qué permite front() y back()?: Mostrar el primero y ultimo elemento dentro de los vectores
    cout << "El primer elemento de v1 es: " << v1.front() << endl;
    cout << "El ultimo elemento de v1 es: " << v1.back() << endl;
    cout << "El primer elemento de v2 es: " << v2.front() << endl;
    cout << "El ultimo elemento de v2 es: " << v2.back() << endl;

    //* ¿qué permite insert?: Sirve para agregar elementos nuevos sin quitar los anteriores dentro del vector
    v1.insert(v1.begin() + 2, 30);
    v2.insert(v2.begin() + 1, "Diana");
    //* ¿qué permite erase?: Elimina elementos de una posición especifica 
    v1.erase(v1.begin()+1);

    //* ¿qué permite pop_back?: Quita los ultimos elementos dentro del vector
    v1.pop_back();
    v2.pop_back();

    // ¿qué permite clear()?: Limpia los el vector sin eliminar los datos 
    v1.clear();

    //¿qué permite empty?: Indica que el vector esta vacio
    if (v1.empty()){
        cout << "El vector v1 esta vacio" << endl;
    }
    else{
        cout << "El vector v1 esta lleno" << endl; 
    }
    if (v2.empty()){
        cout << "El vector v2 esta vacio" << endl;
    }
    else{
        cout << "El vector v2 esta lleno" << endl; 
    }
    // Imprimir vectores v1 y v2
    cout << "[";
    for (int i = 0; i < v1.size(); i++) {
        if (i > 0) cout << ", ";
        cout << v1[i];
    }
    cout << "]" << endl;
    cout<<"--------------------------"<<endl;
        cout << "[";
    for (int i = 0; i < v2.size(); i++) {
        if (i > 0) cout << ", ";
        cout << v2[i];
    }
    cout << "]" << endl;
    


    return 0;
}