#include <iostream>

using namespace std;

int main(){
    //float* dato = new float;
    //*dato = 4.2;
    //cout<<*dato<<endl;
    //delete dato;
    //dato = nullptr;

    int *A = new int[4], k=1;
    for (int i = 0; i < 4; i++)
    {
       A[i] = 0;
       k+=1;
    }
    for (int i = 0; i < 4; ++i)
    {
        cout << A[i] << ",";
    }
    delete[] A;
    A = nullptr;
}