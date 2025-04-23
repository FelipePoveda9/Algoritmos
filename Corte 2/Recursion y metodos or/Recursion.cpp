#include <iostream>

using namespace std;

//Recursiva
int factorial(int n){
    int resultado = 1;
    if (n == 0){
        return 1;
    }
    else{
        resultado = n * factorial(n - 1);
        return resultado;
    }
}

//No recursiva
int nr_factorial (int n){
    int resultado = 1; 
    for (int i = 1; i <= n; i++){
        resultado *= i;
    }
    return resultado;
}

//Recursiva
int fib(int n){
    int resultado = 1;
    if (n <= 1){
        return n;
    }
    else{
        resultado = fib(n - 1) + fib(n - 2);
        return resultado;
    }
}

int main(){
    int n;
    cout << "Ingrese un valor para calcularle el factorial: "<< endl;
    cin >> n;
    cout << "El factorial del numero "<< n << " es: "<< endl << nr_factorial(n) << endl;

    cout << "Ingrese un valor para calcularle el factorial: "<< endl;
    cin >> n;
    cout << "El factorial del numero "<< n << " es: "<< endl << factorial(n) <<endl ;
    cout << "La serie de fibonacci es del numero "<< n <<endl;
    for (int i = 1; i <= n; i++){
        cout << "La serie de fibonacci es: " << i << endl << fib(i) <<endl ;
    }

}