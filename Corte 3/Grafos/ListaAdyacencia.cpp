#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void lista_adyacencia_int(){
    vector<vector<int>> lista_adyacencia(10); 

    lista_adyacencia[0].push_back(1); lista_adyacencia[0].push_back(2);
    lista_adyacencia[1].push_back(3); lista_adyacencia[1].push_back(4);
    lista_adyacencia[2].push_back(5); 
    lista_adyacencia[3].push_back(6);
    lista_adyacencia[4].push_back(5); lista_adyacencia[4].push_back(7);
    lista_adyacencia[5].push_back(8);
    lista_adyacencia[6].push_back(7);
    lista_adyacencia[7].push_back(8); lista_adyacencia[7].push_back(9);
    lista_adyacencia[8].push_back(9);
    lista_adyacencia[9].push_back(0); 


    cout << "Lista adyacencia: " << endl;
    for (int i = 0; i < lista_adyacencia.size(); ++i) 
    {
        cout << i << " -> ";
        for (int j = 0; j < lista_adyacencia[i].size(); ++j) 
        {
            cout << lista_adyacencia[i][j];
            if (j < lista_adyacencia[i].size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

void lista_adyacencia_string(){
    map<string, vector<string>> lista_adyacencia;

    lista_adyacencia["Antioquia"] = {"Huila", "Santander"};
    lista_adyacencia["Santander"] = {"Antioquia", "Arauca"};  
    lista_adyacencia["Arauca"] = {"Santander", "Vichada"};
    lista_adyacencia["Vichada"] = {"Arauca", "Vaupes"};
    lista_adyacencia["Vaupes"] = {"Vichada", "Guaviare"};
    lista_adyacencia["Guaviare"] = {"Vaupes", "Guainia", "Caqueta"};
    lista_adyacencia["Guania"] = {"Guaviare","Meta"};
    lista_adyacencia["Meta"] = {"Huila","Guainia", "Caqueta"};
    lista_adyacencia["Caqueta"] = {"Meta","Putumayo","Guaviare"};
    lista_adyacencia["Huila"] = {"Antioquia","Meta", "Caqueta"};
    lista_adyacencia["Putumayo"] = {"Caqueta", "NULL"};

    for (const auto& par : lista_adyacencia) 
    {
        cout << par.first << " -> ";
        for (const string& cercanos : par.second) 
        {
            cout << cercanos << ", ";
        }
        cout << endl;
    }
}

int main() {
    lista_adyacencia_string();
    return 0;
}
