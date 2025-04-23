#include <iostream>

using namespace std;

void swap(int *px, int *py);

main(){
    int n1, n2;
    cout<<"Ingrese n1: ";
    cin>>n1;
    cout<<"Ingrese n2: ";
    cin>>n2;
    if (n1 > n2)   
        swap(n1,n2);
    cout << "El rango es de " << n1 << " a " << n2 << "." << endl;
    return 0;    
}
void swap(int *px, int *py){
    int tmp = *px;
    *px = *py;
    *py = tmp;
}