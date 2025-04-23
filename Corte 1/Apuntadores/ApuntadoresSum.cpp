#include <iostream>

using namespace std;
int sumArray(int *ptr);

bool esPrimo(int n){
    int recorrer = 0;
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
void noPrimos(int array[]) {
    int recorrer = 0;
    int *ptr = array;
    for (int i = 0; i < 3; i++) {
        if (!esPrimo(array[i])) {
            array[recorrer] = array[i];
            recorrer++;   
        }
    }
    cout << "Números compuestos en el vector: "<< endl;
    for(int i = 0; i < recorrer; i++){
        cout << "Compuestos[" << i << "]: " << array[i]  << endl;
    }
    cout << "La suma es: " << sumArray(array) << endl;
    cout<<"________________________________________________"<<endl;
}

int main(){
    int array[3];
    int *ptr = array;
    cout << "Suma de primos, no primos y multiplos de 3" <<endl;

    for (int i = 0; i < 3; i++){
        cout << "Array[" << i << "]= ";
        cin >> *(ptr + i);
    }
    cout << "La suma es: " << sumArray(array) << endl;

    noPrimos(array);
}

int sumArray(int *ptr){
    int sum = 0;
    int sumComp = 0;
    for (int i = 0; i < 3; i++){
        sum += *ptr++;
    }
    for (int i = 0; i < 3; i++){
        sumComp += *ptr++;
    }
    return sum;
}
