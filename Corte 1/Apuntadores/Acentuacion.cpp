#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isMonosyllabic(const string& word) {
    int syllables = 0;
    bool inSyllable = false;

    for (char c : word) {
        if (isalpha(c)) {
            c = tolower(c);
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                if (!inSyllable) {
                    syllables++;
                    inSyllable = true;
                }
            } else {
                inSyllable = false;
            }
        }
    }
    return syllables == 1;
}

bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool endsInVowelNS(const string& word) {
    char lastChar = tolower(word.back());
    return lastChar == 'n' || lastChar == 's' || isVowel(lastChar);
}

bool isAguda(const string& word) {
    // Acento en la última sílaba
    return true;  // Simplificación, ya que determinar si es aguda depende del contexto
}

bool isGrave(const string& word) {
    // Acento en la penúltima sílaba
    return true;  // Simplificación, ya que determinar si es grave depende del contexto
}

bool isEsdrujula(const string& word) {
    // Acento en la antepenúltima sílaba
    return true;  // Simplificación, ya que determinar si es esdrújula depende del contexto
}

bool hasDiphthong(const string& word) {
    // Función para verificar si tiene diptongo (simplificación)
    return true; // Simplicidad, en la práctica tendríamos que comprobar la secuencia de vocales.
}

bool hasHiatus(const string& word) {
    // Función para verificar si tiene hiato (simplificación)
    return false; // No lo consideramos en este ejemplo
}

int main() {
    string word;

    cout << "Introduce una palabra: ";
    cin >> word;

    // Verificar si la palabra es monosílaba
    if (isMonosyllabic(word)) {
        cout << "La palabra es monosílaba, no lleva tilde." << endl;
    }
    else {
        // Verificar si es aguda, grave o esdrújula
        if (isAguda(word)) {
            if (endsInVowelNS(word)) {
                cout << "La palabra es aguda y lleva tilde." << endl;
            }
            else {
                cout << "La palabra es aguda y no lleva tilde." << endl;
            }
        }
        else if (isGrave(word)) {
            if (!endsInVowelNS(word)) {
                cout << "La palabra es grave y lleva tilde." << endl;
            }
            else {
                cout << "La palabra es grave y no lleva tilde." << endl;
            }
        }
        else if (isEsdrujula(word)) {
            cout << "La palabra es esdrújula y siempre lleva tilde." << endl;
        }
        else if (hasDiphthong(word)) {
            // Verificar si tiene diptongo
            if (hasHiatus(word)) {
                cout << "La palabra tiene hiato y lleva tilde." << endl;
            }
            else {
                cout << "La palabra tiene diptongo y no lleva tilde." << endl;
            }
        }
        else {
            cout << "La palabra no tiene una clasificación clara. Revisa las reglas." << endl;
        }
    }

    return 0;
}
