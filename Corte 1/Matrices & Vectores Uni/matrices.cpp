#include <iostream>

using namespace std;
bool esPrimo(int n){
    if (n <= 1){
        return true;
    }
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0){ 
            return false;
        }
    }
    return true;
}
bool mult(int num) {
    if (num % 5 == 0) {
        return true;
    }
    return false; 
}

void noPrimos(int m[][5]) {
    int a[20];
    int recorrer = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if (!esPrimo(m[i][j])) {
                a[recorrer] = m[i][j];
                recorrer++;   
            }
        }
    }
    cout << "Números no primos en la matriz: "<< endl;
    for(int i = 0; i < recorrer; i++){
        cout << "No primos[" << a[i] << "]"  << endl;
    }
    cout<<"________________________________________________"<<endl;
}
void divisible(int m[][5]){
    int b[20];
    int recorrer = 0;
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
        if (mult(m[i][j])) {
            b[recorrer] = m[i][j];
            recorrer++;   
            }
        }
    }
    cout << "Números multiplos de 5 en la matriz: "<< endl;
    for(int i = 0; i < recorrer; i++){
        cout << "Mod5[" << b[i] << "]"  << endl;
    }
    cout<<"________________________________________________"<<endl;
}
void mCreada(int m[][5]){
    for (int i = 0; i<4; i++)
    {
        for(int j=0; j<5; j++)
        {
            m[i][j] = rand() % 100;
            cout << "m[" << i << "][" << j << "]: " << m[i][j];
            cout<<endl;
        } 
    }
    cout<<"________________________________________________"<<endl;
    for (int i = 0; i<4; i++)
    {
        for(int j=0; j<5; j++)
        {
            cout << "-" << "-{"<<m[i][j]<<"}-"<<"-";
        }
    cout<<endl;
    }
    cout<<"________________________________________________"<<endl; 
}
void suma(int m[][5]){
    int suma = 0; 
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            suma = suma + m[i][j];
        }
    }
    cout<<"La suma de la matriz es: "<< suma <<endl;
}
main(){
    int m[4][5];
    int a[20];
        cout<<"____________"<<endl;
        mCreada(m);
        noPrimos(m);
        divisible(m);
        suma(m);
        cout<<"________________________________________________"<<endl;   
    return 0;
}