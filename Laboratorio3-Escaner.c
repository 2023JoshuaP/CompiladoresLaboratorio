#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAYOR '>'
#define PUNTOYCOMA ';'
#define PARI '('
#define ID 256
#define NUM 257
#define MAYORIGUAL 258
#define WHILE 259
#define IF 260

int scaner();
void mostrar(int);
int espalres();

FILE *f;
char lexema[80];

int main(int argc, char *argv[]) {
    int token;
    f = stdin;  // entrada estándar del teclado
    if (argc == 2) {  // si se especificó un archivo de lectura
        f = fopen(argv[1], "rt");  // lectura en modo texto
        if (f == NULL)
            f = stdin;
    }
    if (f == stdin)  // la lectura será desde la entrada estándar
        printf("Ingrese texto ........ termine con Ctrl+Z\n");
    while (1) {
        token = scaner();
        if (token == EOF) break;
        mostrar(token);
    }
    if (f != stdin)  // si la entrada fue de un archivo
        fclose(f);  // entonces cerrar el archivo
    return 0;
}

int scaner() {
    int c;
    int i;
    do {
        c = fgetc(f);
    } while (isspace(c));  // ignora espacios en blanco
    if (c == EOF) return EOF;
    if (isalpha(c)) {  // regla del ID
        i = 0;
        do {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isalnum(c) || c == '_');
        lexema[i] = 0;
        ungetc(c, f);  // se devuelve c al flujo de entrada
        i = espalres();  // verifica si es palabra reservada
        if (i >= 0)
            return i;
        return ID;  // se trata de un ID
    }
    if (isdigit(c)) {  // regla del NUM
        i = 0;
        do {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isdigit(c));

        lexema[i] = 0;
        ungetc(c, f);
        return NUM;
    }
    // regla de PUNTOYCOMA y PARI
    if ((c == ';') || (c == '(')) return c;  // regla del ";" y "("
    if (c == '>') {  // regla de ">" o ">="
        c = fgetc(f);
        if (c == '=') {  // return MAYORIGUAL
            lexema[0] = '>';
            lexema[1] = '=';
            lexema[2] = 0;
            return MAYORIGUAL;
        }
        ungetc(c, f);
        return MAYOR;  // return MAYOR
    }
    return c;  // para otros caracteres no definidos, devolver el carácter en sí
}

int espalres() {
    if (strcmp(lexema, "while") == 0) return WHILE;
    if (strcmp(lexema, "if") == 0) return IF;

    return -1;
}

void mostrar(int token) {
    switch (token) {
        case ID:
            printf("token = ID [%s] \n", lexema);
            break;
        case NUM:
            printf("token = NUM [%s] \n", lexema);
            break;
        case MAYORIGUAL:
            printf("token = MAYORIGUAL [%s] \n", lexema);
            break;
        case WHILE:
            printf("token = WHILE [%s] \n", lexema);
            break;
        case IF:
            printf("token = IF [%s] \n", lexema);
            break;
        case PARI:
            printf("token = PARI [%c] \n", token);
            break;
        case MAYOR:
            printf("token = MAYOR [%c] \n", token);
            break;
        case PUNTOYCOMA:
            printf("token = PUNTOYCOMA [%c] \n", token);
            break;
        default:
            printf("token desconocido [%c] \n", token);
            break;
    }
}