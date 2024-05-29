#include <iostream>
#include <cctype>
#include <string>
using namespace std;

enum Simbolos {
    LETRA,
    DIGITO,
    FDC,
    ERROR,
};

Simbolos entradaVariables(char c) {
    if (isalpha(c)) {
        return LETRA;
    }
    if (isdigit(c)) {
        return DIGITO;
    }
    if (c == '\0') {
        return FDC;
    }
    return ERROR;
}

string analizarVariables(const string& cadena) {
    int transiciones[3][4] = {
        {3,2,2,2},
        {2,2,2,2},
        {3,3,3,2},
    };
    int estado = 1;
    cerr << "Estado Incial: " << estado << endl;
    for (size_t i = 1; i <= cadena.length(); i++) {
        char simbolo = (i < cadena.length()) ? cadena[i] : '\0';
        Simbolos tipoEntrada = entradaVariables(simbolo);

        if (tipoEntrada == ERROR) {
            return "Error";
        }
        estado = transiciones[estado - 1][tipoEntrada];
        cerr << "Nuevo estado: " << estado << endl;
        if (estado == 2) {
            return "Error";
        }

        if (tipoEntrada == FDC) {
            break;
        }
    }
    if (estado == 3) {
        return "Cadena Valida";
    }
    else {
        return "Error";
    }
}

int main() {
    string cadena = "hola123";
    string resultado = analizarVariables(cadena);
    cout << resultado << endl;
    return 0;
}