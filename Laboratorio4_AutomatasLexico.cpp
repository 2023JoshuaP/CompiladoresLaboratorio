#include <iostream>
#include <cctype>
#include <string>

using namespace std;

// Función para verificar si un carácter es una letra
bool esLetra(char c) {
    return isalpha(c);
}

// Función para verificar si un carácter es un dígito
bool esDigito(char c) {
    return isdigit(c);
}

// Función principal para analizar la cadena
string analizarCadena(const string& entrada) {
    int estado = 1;
    size_t i = 0;

    while (i < entrada.length()) {
        char simbolo = entrada[i];

        switch (estado) {
            case 1:
                if (esLetra(simbolo)) {
                    estado = 3;
                } else if (esDigito(simbolo)) {
                    estado = 2;
                } else {
                    return "Error";
                }
                break;
            case 2:
                return "Error";
            case 3:
                if (esLetra(simbolo) || esDigito(simbolo)) {
                    estado = 3;
                } else {
                    return "Error";
                }
                break;
            default:
                return "Error";
        }

        i++;
    }

    if (estado == 3) {
        return "Cadena válida";
    } else {
        return "Error";
    }
}

int main() {
    string cadena = "c";
    string resultado = analizarCadena(cadena);
    cout << "Resultado del análisis para '" << cadena << "': " << resultado << endl;
    return 0;
}