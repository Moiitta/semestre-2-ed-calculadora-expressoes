#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fila.h"
#include "basics.h"

boolean ehOperador(char c) {
    return (c == '+' || 
            c == '-' || 
            c == '*' || 
            c == '/' || 
            c == '^' || 
            c == '(' || 
            c == ')');
}

boolean removeEspacosValidando(char *str) {
    int i, j = 0;
    int tamanho = strlen(str);

    for (i = 0; i < tamanho; i++) {
        if (!(isdigit((unsigned char)str[i]) || ehOperador(str[i]) || isspace((unsigned char)str[i]))) {
            printf("Erro: caractere inválido: %c\n", str[i]);
            return false;
        }
        // Verifica se o digito atual é espaço e está entre dígitos 
        if (isspace((unsigned char)str[i])) {
            if (i > 0 && isdigit((unsigned char)str[i - 1]) &&
                isdigit((unsigned char)str[i + 1])) {
                return false; 
            }
            continue;
        }
        str[j] = str[i];
        j++;
    }

    str[j] = '\0';
    return true;
}

boolean converteTokens(Fila* fila, char* expressao) {

    int tamanho = strlen(expressao);
    int i,j = 0;
    char temp[32];

    for(i = 0; i < tamanho; i++) {
        if(isdigit((unsigned char)expressao[i]) == true) {
            temp[j] = expressao[i];
            j++;

            if(isdigit((unsigned char)expressao[i + 1]) == false) {
                temp[j] = '\0';
                j = 0;
                guarde_na_fila(fila, (ElementoDeFila)strdup(temp));
            }
        } else {
            char op[2] = {expressao[i], '\0'};
            guarde_na_fila(fila, strdup(op));
        }
    }

    return true;
}

boolean calculaExpressao(char* expressao, float* resultado) {
    boolean ok = removeEspacosValidando(expressao);
    Fila fila;

    nova_fila(&fila, 100);

    if (!ok) { 
        printf("Erro: expressao inválida (espaço entre digitos).\n");
        return false;
    }

    ok = converteTokens(&fila, expressao);

    if (!ok) { 
        printf("Erro: Erro ao converter em tokens.\n");
        return false;
    }

    printf("Tokens gerados:\n");
    ElementoDeFila e;
    while (!fila_vazia(fila)) {
        recupere_da_fila(fila, &e);
        printf("  %s\n", (char*)e);
        remova_elemento_da_fila(&fila);
    }

    // Colocando um valor qualquer enquanto não tem toda a implementação
    *resultado = 1.0; 
    return true;
}

int main() {
    char texto[100];
    float resultado;

    printf("Digite uma expressao: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0';

    if (calculaExpressao(texto, &resultado) == false) {
        return 1;
    }

    printf("Expressao valida! Resultado = %s\n", texto);
    return 0;
}
