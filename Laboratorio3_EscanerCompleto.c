#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAYOR '>'
#define MENOR '<'
#define IGUAL '='
#define NOT '!'
#define PUNTOYCOMA ';'
#define COMA ','
#define PARI '('
#define PARD ')'
#define CORI '['
#define CORD ']'
#define LLAVEI '{'
#define LLAVED '}'
#define ID 256
#define NUM 257
#define MAYORIGUAL 258
#define MENORIGUAL 259
#define IGUALDAD 260
#define DISTINTO 261
#define WHILE 262
#define IF 263
#define FOR 264
#define ELSE 265
#define RETURN 266
#define ELSEIF 267
#define SWITCH 268
#define CASE 269
#define NEW 270
#define DELETE 271
#define COUT 272
#define CIN 273
#define INCLUDE 274
#define USING 275
#define NAMESPACE 276

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
    } while (isspace(c));  // ignorar espacios en blanco

    if (c == EOF) return EOF;

    if (c == '/') {  // manejar comentarios
        c = fgetc(f);
        if (c == '/') {  // comentario de línea
            while (c != '\n' && c != EOF) {
                c = fgetc(f);
            }
            return scaner();  // continuar escaneando después del comentario
        } else if (c == '*') {  // comentario de bloque
            while (1) {
                c = fgetc(f);
                if (c == EOF) return EOF;
                if (c == '*') {
                    c = fgetc(f);
                    if (c == '/') break;  // fin del comentario de bloque
                }
            }
            return scaner();  // continuar escaneando después del comentario
        } else {
            ungetc(c, f);
            return '/';
        }
    }
    if (isalpha(c)) {  // regla para ID
        i = 0;
        do {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isalnum(c) || c == '_');

        lexema[i] = 0;
        ungetc(c, f);  // devolver c al flujo de entrada
        i = espalres();  // comprobar si es una palabra reservada
        if (i >= 0)
            return i;
        return ID;  // es un ID
    }
    if (isdigit(c)) {  // regla para NUM
        i = 0;
        do {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isdigit(c));

        lexema[i] = 0;
        ungetc(c, f);
        return NUM;
    }
    // reglas para tokens de un solo carácter
    if (c == ';') return PUNTOYCOMA;
    if (c == ',') return COMA;
    if (c == '(') return PARI;
    if (c == ')') return PARD;
    if (c == '[') return CORI;
    if (c == ']') return CORD;
    if (c == '{') return LLAVEI;
    if (c == '}') return LLAVED;
    // reglas para tokens de múltiples caracteres
    if (c == '>') {
        int next = fgetc(f);
        if (next == '=') {
            lexema[0] = '>';
            lexema[1] = '=';
            lexema[2] = 0;
            return MAYORIGUAL;
        }
        ungetc(next, f);
        return MAYOR;
    }
    if (c == '<') {
        int next = fgetc(f);
        if (next == '=') {
            lexema[0] = '<';
            lexema[1] = '=';
            lexema[2] = 0;
            return MENORIGUAL;
        }
        ungetc(next, f);
        return MENOR;
    }
    if (c == '=') {
        int next = fgetc(f);
        if (next == '=') {
            lexema[0] = '=';
            lexema[1] = '=';
            lexema[2] = 0;
            return IGUALDAD;
        }
        ungetc(next, f);
        return IGUAL;
    }
    if (c == '!') {
        int next = fgetc(f);
        if (next == '=') {
            lexema[0] = '!';
            lexema[1] = '=';
            lexema[2] = 0;
            return DISTINTO;
        }
        ungetc(next, f);
        return NOT;
    }

    return c;  // para otros caracteres no definidos, devolver el carácter en sí
}

int espalres() {
    if (strcmp(lexema, "while") == 0) return WHILE;
    if (strcmp(lexema, "if") == 0) return IF;
    if (strcmp(lexema, "else") == 0) return ELSE;
    if (strcmp(lexema, "for") == 0) return FOR;
    if (strcmp(lexema, "return") == 0) return RETURN;
    if (strcmp(lexema, "switch") == 0) return SWITCH;
    if (strcmp(lexema, "case") == 0) return CASE;
    if (strcmp(lexema, "new") == 0) return NEW;
    if (strcmp(lexema, "delete") == 0) return DELETE;
    if (strcmp(lexema, "cout") == 0) return COUT;
    if (strcmp(lexema, "cin") == 0) return CIN;
    if (strcmp(lexema, "include") == 0) return INCLUDE;
    if (strcmp(lexema, "using") == 0) return USING;
    if (strcmp(lexema, "namespace") == 0) return NAMESPACE;
    // añadir otras palabras reservadas aquí

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
        case MENORIGUAL:
            printf("token = MENORIGUAL [%s] \n", lexema);
            break;
        case IGUALDAD:
            printf("token = IGUALDAD [%s] \n", lexema);
            break;
        case DISTINTO:
            printf("token = DISTINTO [%s] \n", lexema);
            break;
        case WHILE:
            printf("token = WHILE [%s] \n", lexema);
            break;
        case IF:
            printf("token = IF [%s] \n", lexema);
            break;
        case ELSE:
            printf("token = ELSE [%s] \n", lexema);
            break;
        case FOR:
            printf("token = FOR [%s] \n", lexema);
            break;
        case RETURN:
            printf("token = RETURN [%s] \n", lexema);
            break;
        case ELSEIF:
            printf("token = ELSEIF [%s] \n", lexema);
            break;
        case SWITCH:
            printf("token = SWITCH [%s] \n", lexema);
            break;
        case CASE:
            printf("token = CASE [%s] \n", lexema);
            break;
        case NEW:
            printf("token = NEW [%s] \n", lexema);
            break;
        case DELETE:
            printf("token = DELETE [%s] \n", lexema);
            break;
        case COUT:
            printf("token = COUT [%s] \n", lexema);
            break;
        case CIN:
            printf("token = CIN [%s] \n", lexema);
            break;
        case INCLUDE:
            printf("token = INCLUDE [%s] \n", lexema);
            break;
        case NAMESPACE:
            printf("token = NAMESPACE [%s] \n", lexema);
            break;
        case PARI:
            printf("token = PARI [%c] \n", token);
            break;
        case PARD:
            printf("token = PARD [%c] \n", token);
            break;
        case CORI:
            printf("token = CORI [%c] \n", token);
            break;
        case CORD:
            printf("token = CORD [%c] \n", token);
            break;
        case LLAVEI:
            printf("token = LLAVEI [%c] \n", token);
            break;
        case LLAVED:
            printf("token = LLAVED [%c] \n", token);
            break;
        case PUNTOYCOMA:
            printf("token = PUNTOYCOMA [%c] \n", token);
            break;
        case COMA:
            printf("token = COMA [%c] \n", token);
            break;
        case MAYOR:
            printf("token = MAYOR [%c] \n", token);
            break;
        case MENOR:
            printf("token = MENOR [%c] \n", token);
            break;
        case IGUAL:
            printf("token = IGUAL [%c] \n", token);
            break;
        case NOT:
            printf("token = NOT [%c] \n", token);
            break;
        case '+':
            printf("token = SUMA [%c] \n", token);
            break;
        case '-':
            printf("token = RESTA [%c] \n", token);
            break;
        case '*':
            printf("token = MULTIPLICACION [%c] \n", token);
            break;
        case '/':
            printf("token = DIVISION [%c] \n", token);
            break;
        default:
            printf("token desconocido [%c] \n", token);
            break;
    }
}