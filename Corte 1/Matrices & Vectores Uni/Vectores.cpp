#include <iostream>

using namespace std;

bool num_primo(int num) {
    int divisor=2; 
    while(num%divisor != 0){
    divisor++;
    }  
    if(num==divisor){
        return true;
    }
    else{
        return false;
    }
}

void leer_num(int num[]) {
    cout << "Los numeros generados son:\n";
    for (int i = 0; i < 6; i++) 
    {
        num[i] = rand() % 100;
        cout << "num[" << i << "] = " << num[i] << endl;
    }

    cout << "Los numeros primos son:"<<endl;
    for (int i = 0; i < 6; i++) 
    {
        if (num_primo(num[i])) 
        {
            cout << "num[" << i << "] = " << num[i] << endl;
        }
    }
}

void buscar_dato(int num[]) {
    int dato, encontrado = 0;
    cout << "Ingrese el dato que quiere buscar: ";
    cin >> dato;
    
    for (int i = 0; i < 6; i++) {
        if (num[i] == dato) 
        {
            cout << "Su dato esta en la posicion num[" << i << "]"<<endl;
            encontrado = 1;
        }
    }
    if (!encontrado) 
    {
        cout << "El dato no existe en el vector" <<endl;
    }
}

int main() {
    int num[6];
    leer_num(num);
    buscar_dato(num);
    return 0;
}