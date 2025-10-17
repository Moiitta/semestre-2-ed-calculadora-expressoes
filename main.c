#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "basics.h"


boolean removeEspacosValidando(char *str) {
    // TODO: validar se existem apenas numeros e operadores
    int i, j = 0;
    int tamanho = strlen(str);

    for (i = 0; i < tamanho; i++) {
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

boolean calculaExpressao(char* expressao, float* resultado) {
    boolean ok = removeEspacosValidando(expressao);

    if (!ok) { 
        return false;
    }

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
        printf("Erro: expressao inválida (espaço entre digitos).\n");
        return 1;
    }

    printf("Expressao valida! Resultado = %.2f\n", resultado);
    return 0;
}
