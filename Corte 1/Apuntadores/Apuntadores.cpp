#include <iostream>
using namespace std;

void pruebas(){
    double list[3];
    double *p;
    p = list;
    p = &list[2];
    list[0] = 1.0;
    list[1] = 1.5;
    list[2] = 2.0;
    cout << "List: " << list << endl;
    cout << "p: " << p << endl;
    cout << "*p: " << *p << endl; 
}
main(){
    int *p1,*p2;
    int x = 42,y = 163;
    p1 = &x;
    p2 = &y;

    cout<<"x: "<< x << endl;
    cout<<"y: "<< y << endl;;
    cout<<"p1: "<< p1 << endl;;
    cout<<"p2: "<< p2 << endl;;
    cout<<"*p1: "<< *p1 << endl;;
    cout<<"*p2: "<< *p2 << endl;;
    pruebas();
    return 0;
}


